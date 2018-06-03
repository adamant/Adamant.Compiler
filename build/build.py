#!/usr/bin/python3

import sys

if (sys.version_info < (3, 0)):
    print('Python Verion >=3.0 required')
    exit(1)

import colorama, argparse
from termcolor import colored
from make import *
from git import Repo

colorama.init()

build_path = 'target2'

def main():
    parser = argparse.ArgumentParser(description='A make like build system')
    parser.add_argument('targets', nargs='*',
                    help='the target(s) to build')
    # TODO add --watch argument that starts watching the target afterward
    args = parser.parse_args()
    step = start_step('Total Build')
    if not args.targets:
        args.targets.append('build')
    for target in args.targets:
        print(colored('Building target: {0}'.format(target), 'blue'))
        if target == 'build':
            build()
        elif target == 'build-previous':
            build_previous()
        elif target == 'clean':
            clean()
        else:
            print(colored('Unknown build target "{0}"'.format(target), 'red'))
    end_step(step)

def build():
    build_previous()

def build_previous():
    checkout_translated()
    step = start_step('Build Previous')
    end_step(step)

def clean():
    step = start_step('Clean')
    ensure_directory_exists(build_path)
    clean_directory(build_path)
    end_step(step)

compiler_repo = Repo('.')

def building_commit():
    # Checks if there are any modified uncommited files or untracked files
    if compiler_repo.head.commit.diff(None) or compiler_repo.untracked_files:
        print(colored('  Building uncommitted changes', 'yellow'))
        return None
    else:
        print('  Building commit: {0}'.format(compiler_repo.head.commit.hexsha))
        return compiler_repo.head.commit

def parent_commit():
    step = start_step('Parent Commit')
    current_commit = building_commit()
    if current_commit == "<none>":
        parent_commit = current_commit.parents[0] # TODO What if this is a merge commit?
    else:
        parent_commit = compiler_repo.head.commit
    print('  Parent commit: {0}'.format(parent_commit.hexsha))
    end_step(step)
    return parent_commit

translated_repo_path = os.path.join(build_path, 'translated-repo')

def clone_translated_repo():
    step = start_step("Clone Translated Repo")
    try:
        ensure_directory_exists(build_path)
        Repo(translated_repo_path).git_dir # git_dir to force an exception if it isn't valid
        print('  Translated repo exists, skipping clone')
    except:
        Repo.clone_from('https://github.com/adamant/adamant.tools.compiler.translated.git', translated_repo_path)
    end_step(step)

def checkout_translated():
    clone_translated_repo()
    compiler_commit = parent_commit()
    step = start_step('Checkout Translated')
    translated_repo = Repo(translated_repo_path)
    translated_repo.git.fetch('--tags')
    while True:
        try:
            tag = translated_repo.tag('refs/tags/translated/'+compiler_commit.hexsha)
            tag.commit.hexsha # force a fetch so we know the tag exists
            break
        except ValueError:
            print('  No source for commit ' + compiler_commit.hexsha)
            compiler_commit = compiler_commit.parents[0] # TODO What if this is a merge commit?

    print('  Checking out translated/{} hash: {}'.format(compiler_commit.hexsha, tag.commit.hexsha))
    if translated_repo.head.commit.hexsha == tag.commit.hexsha \
            and compiler_repo.head.commit.diff(None) or compiler_repo.untracked_files:
        print('  Already cleanly checked out')
    else:
        translated_repo.head.reference = tag.commit
        translated_repo.head.reset(index=True, working_tree=True)
    end_step(step)

if __name__ == "__main__":
    main()
