# adamant.tools.compiler.semantics.names.lookup

This namespace provides what is essentially the symbol table used during name binding.  Perhaps this should actually be more directly related to symbols. If there were `Unbound_Symbol`s that were the base type for `Bound_Symbol`s where bound symbols were tied to declarations in `Semantic_Node`s then unbound symbols could be used for this. This would allow the symbols for other packages to be directly used as the name table for that package.

Also, right now this is a mutable structure that includes parent references. For this structure to be reusable, it would need to be immutable and not have parent references. This could be handled by doing Roslyn style red and green trees. However, the red nodes could be structs constructed on the fly and borrowing references to the red nodes above them. This would be a super cheap way to keep a chain of parent references without doing extra allocation. This could actually be a really useful idiom in the langauge

TODO change these to scope and have different types. Types include:

* global scope
* function scope
* namespace/module scope
* block scope

see https://en.wikipedia.org/wiki/Scope_(computer_science)#Levels_of_scope
