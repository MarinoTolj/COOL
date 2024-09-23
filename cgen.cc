
//**************************************************************
//
// Code generator SKELETON
//
// Read the comments carefully. Make sure to
//    initialize the base class tags in
//       `CgenClassTable::CgenClassTable'
//
//    Add the label for the dispatch tables to
//       `IntEntry::code_def'
//       `StringEntry::code_def'
//       `BoolConst::code_def'
//
//    Add code to emit everyting else that is needed
//       in `CgenClassTable::code'
//
//
// The files as provided will produce code to begin the code
// segments, declare globals, and emit constants.  You must
// fill in the rest.
//
//**************************************************************

#include "cgen.h"
#include "cgen_gc.h"
#include <map>
extern void emit_string_constant(ostream &str, char *s);
extern int cgen_debug;

//
// Three symbols from the semantic analyzer (semant.cc) are used.
// If e : No_type, then no code is generated for e.
// Special code is generated for new SELF_TYPE.
// The name "self" also generates code different from other references.
//
//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
Symbol
    arg,
    arg2,
    Bool,
    concat,
    cool_abort,
    copy,
    Int,
    in_int,
    in_string,
    IO,
    length,
    Main,
    main_meth,
    No_class,
    No_type,
    Object,
    out_int,
    out_string,
    prim_slot,
    self,
    SELF_TYPE,
    Str,
    str_field,
    substr,
    type_name,
    val;
//
// Initializing the predefined symbols.
//
static void initialize_constants(void)
{
    arg = idtable.add_string("arg");
    arg2 = idtable.add_string("arg2");
    Bool = idtable.add_string("Bool");
    concat = idtable.add_string("concat");
    cool_abort = idtable.add_string("abort");
    copy = idtable.add_string("copy");
    Int = idtable.add_string("Int");
    in_int = idtable.add_string("in_int");
    in_string = idtable.add_string("in_string");
    IO = idtable.add_string("IO");
    length = idtable.add_string("length");
    Main = idtable.add_string("Main");
    main_meth = idtable.add_string("main");
    //   _no_class is a symbol that can't be the name of any
    //   user-defined class.
    No_class = idtable.add_string("_no_class");
    No_type = idtable.add_string("_no_type");
    Object = idtable.add_string("Object");
    out_int = idtable.add_string("out_int");
    out_string = idtable.add_string("out_string");
    prim_slot = idtable.add_string("_prim_slot");
    self = idtable.add_string("self");
    SELF_TYPE = idtable.add_string("SELF_TYPE");
    Str = idtable.add_string("String");
    str_field = idtable.add_string("_str_field");
    substr = idtable.add_string("substr");
    type_name = idtable.add_string("type_name");
    val = idtable.add_string("_val");
}

// lookup name in locals and current class's attrs.
std::tuple<bool, llvm::Value *, int> llvm_lookup_var(Symbol name)
{
    llvm::Value **loc = llvm_tmp_table.lookup(name);

    if (loc == NULL)
        return std::make_tuple(true, nullptr, cur_node->get_llvm_attr_offset(name));
    else
        return std::make_tuple(false, *loc, 0);
}
// Handles the creation of primitive Basic classes(Int, Str, Bool).
// For Str class you will need to update length field manually.
llvm::Value *get_primitive(Symbol primitiveName, Builder &builder, Module &module, llvm::Value *value)
{
    llvm::Function *malloc = module->getFunction("malloc");
    if (primitiveName == Int)
    {
        auto int_init = module->getFunction((std::string) "Int" + CLASSINIT_SUFFIX);

        //  class tag: 4 + Object size: 4 + Disp Table: 8 + int_field: 4=20
        llvm::Value *mallocCall = builder->CreateCall(malloc, builder->getInt32(20));
        llvm::Value *intClassInstance = builder->CreateBitCast(mallocCall, int_init->getArg(0)->getType());
        builder->CreateCall(int_init, intClassInstance);

        auto int_field = builder->CreateStructGEP(intClassInstance->getType()->getPointerElementType(), intClassInstance, 0 + DEFAULT_OBJFIELDS);
        builder->CreateStore(value, int_field);
        return intClassInstance;
    }
    else if (primitiveName == Str)
    {
        auto str_init = module->getFunction((std::string) "String" + CLASSINIT_SUFFIX);
        // class size
        //  class tag: 4 + Object size: 4 + Disp Table: 8 + ptr_to_Int: 8 + ptr_to_chars: 8=32
        llvm::Value *mallocCall = builder->CreateCall(malloc, builder->getInt32(32));
        llvm::Value *strClassInstance = builder->CreateBitCast(mallocCall, str_init->getArg(0)->getType());
        builder->CreateCall(str_init, strClassInstance);
        llvm::Value *str_field = builder->CreateStructGEP(strClassInstance->getType()->getPointerElementType(), strClassInstance, 1 + DEFAULT_OBJFIELDS);

        builder->CreateStore(value, str_field);

        return strClassInstance;
    }
    else if (primitiveName == Bool)
    {
        auto bool_init = module->getFunction((std::string) "Bool" + CLASSINIT_SUFFIX);
        // class size
        //  class tag: 4 + Object size: 4 + Disp Table: 8 + i1_field=17
        llvm::Value *mallocCall = builder->CreateCall(malloc, builder->getInt32(17));
        llvm::Value *boolClassInstance = builder->CreateBitCast(mallocCall, bool_init->getArg(0)->getType());
        builder->CreateCall(bool_init, boolClassInstance);

        auto bool_field = builder->CreateStructGEP(boolClassInstance->getType()->getPointerElementType(), boolClassInstance, 0 + DEFAULT_OBJFIELDS);
        builder->CreateStore(value, bool_field);
        return boolClassInstance;
    }
}

bool is_subtype(CgenNodeP subtype, CgenNodeP supertype)
{

    if (subtype->get_name() == Object)
        return false;
    if (supertype->get_name() == Object || subtype->get_name() == supertype->get_name() || subtype->get_name() == No_type || subtype->get_name() == SELF_TYPE)
        return true;

    if (subtype->get_parent() == supertype->get_name())
        return true;

    return is_subtype(subtype->get_parentnd(), supertype);
}
Symbol get_lub(CgenNodeP c1, CgenNodeP c2)
{

    if (c1->get_name() == Object || c2->get_name() == Object)
        return Object;

    if (c1->get_name() == c2->get_name())
        return c1->get_name();

    if (c1->get_parent() == c2->get_parent())
        return c1->get_parent();

    if (is_subtype(c1, c2))
        return c2->get_name();

    if (is_subtype(c2, c1))
        return c1->get_name();

    return get_lub(c1->get_parentnd(), c2);
}

llvm::Type *get_llvm_type(Symbol cool_type, Symbol className)
{
    return class_table->probe(cool_type == SELF_TYPE ? className : cool_type)->get_struct_type()->getPointerTo();
}

//*********************************************************
//
// Define method for code generation
//
// This is the method called by the compiler driver
// `cgtest.cc'. cgen takes an `ostream' to which the assembly will be
// emmitted, and it passes this and the class list of the
// code generator tree to the constructor for `CgenClassTable'.
// That constructor performs all of the work of the code
// generator.
//
//*********************************************************

void program_class::cgen(ostream &os, char *filename)
{

    initialize_constants();
    CgenClassTable *codegen_classtable = new CgenClassTable(classes, os, filename);
}

void set_tags(CgenNodeP node)
{
    if (cgen_debug)
        cout << "tag: " << tag_cnt << " - " << node->name << endl;

    node->tag = tag_cnt++;
    for (List<CgenNode> *cld = node->get_children(); cld != NULL; cld = cld->tl())
    {
        set_tags(cld->hd());
    }
}

// TODO: pocetak

CgenClassTable::CgenClassTable(Classes classes, ostream &s, char *filename) : nds(NULL), str(s)
{

    enterscope();

    llvm_tmp_table.enterscope();

    module_init();
    module->setTargetTriple("x86_64-pc-linux-gnu");

    if (cgen_debug)
        cout << "Building CgenClassTable" << endl;
    install_basic_classes();
    install_classes(classes);
    build_inheritance_tree();

    set_tags(root());
    stringclasstag = probe(Str)->tag; /* Change to your String class tag here */
    intclasstag = probe(Int)->tag;    /* Change to your Int class tag here */
    boolclasstag = probe(Bool)->tag;  /* Change to your Bool class tag here */

    code();
    class_table = this;

    // For llvm
    ofstream out("./llvm/hello_world.out");

    code_extern_fn();
    std::vector<llvm::Constant *> strings;

    llvm_code_class_name(root(), strings);

    llvm::ArrayType *ArrayType = llvm::ArrayType::get(builder->getInt8PtrTy(), strings.size());
    llvm::Constant *ArrayConstant = llvm::ConstantArray::get(ArrayType, strings);

    new llvm::GlobalVariable(
        *module.get(), ArrayType, true, llvm::GlobalValue::PrivateLinkage, ArrayConstant, ".str_array");

    builder->CreateGlobalStringPtr(filename, "file_name", 0, module.get());
    builder->CreateGlobalStringPtr(": Dispatch to void.\n", "_dispatch_msg", 0, module.get());
    builder->CreateGlobalStringPtr("No match in case statement for Class ", "_case_abort", 0, module.get());
    builder->CreateGlobalStringPtr("Match on void in case statement.\n", "_case_abort2", 0, module.get());

    llvm_code_prototype_objects(root());
    llvm_code_class_methods(root());

    llvm_code_class_to_structs(root());
    llvm_code_dispatch_tables(root());
    llvm_code_object_initializers(root());

    // Object methods
    code_abort();
    code_type_name();
    code_copy();
    // IO methods
    code_out_string();
    code_out_int();
    code_in_string();
    code_in_int();
    // String methods
    code_length();
    code_concat();
    code_substring();

    llvm_code_class(root(), &out);
    std::string out_filename(filename);
    std::size_t lastSlashPos = out_filename.find_last_of("/");
    std::size_t lastDotPos = out_filename.find_last_of(".");
    out_filename = out_filename.substr(lastSlashPos + 1, lastDotPos - lastSlashPos - 1);

    save_module_to_file((std::string) ".//test_files//res//" + out_filename + (std::string) ".ll");
    // save_module_to_file("./llvm/hello_world.ll");
    exitscope();
    llvm_tmp_table.exitscope();
}
void CgenClassTable::code_extern_fn()

{
    // malloc
    llvm::Function::Create(llvm::FunctionType::get(builder->getInt8PtrTy(), builder->getInt32Ty(), false),
                           llvm::Function::ExternalLinkage, "malloc", module.get());
    // memcpy
    llvm::Function::Create(llvm::FunctionType::get(builder->getInt8PtrTy(),
                                                   {builder->getInt8PtrTy(), builder->getInt8PtrTy(), builder->getInt32Ty()}, false),
                           llvm::Function::ExternalLinkage, "memcpy", module.get());
    // printf
    llvm::Function::Create(llvm::FunctionType::get(builder->getInt32Ty(),
                                                   {builder->getInt8PtrTy()}, true),
                           llvm::Function::ExternalLinkage, "printf", module.get());
    // scanf
    llvm::Function::Create(llvm::FunctionType::get(builder->getInt32Ty(),
                                                   {builder->getInt8PtrTy()}, true),
                           llvm::Function::ExternalLinkage, "scanf", module.get());
    // strlen
    llvm::Function::Create(llvm::FunctionType::get(builder->getInt32Ty(),
                                                   {builder->getInt8PtrTy()}, false),
                           llvm::Function::ExternalLinkage, "strlen", module.get());
    // exit
    llvm::Function::Create(llvm::FunctionType::get(builder->getVoidTy(),
                                                   {builder->getInt32Ty()}, false),
                           llvm::Function::ExternalLinkage, "exit", module.get());
};
void CgenClassTable::llvm_code_class_name(CgenNodeP node, std::vector<llvm::Constant *> &strings)
{

    auto className = module->getNamedGlobal(node->get_name()->get_string());
    llvm::Constant *Zero = llvm::ConstantInt::get(builder->getInt32Ty(), 0);
    strings.push_back(llvm::ConstantExpr::getInBoundsGetElementPtr(className->getValueType(), className, llvm::ArrayRef<llvm::Constant *>{Zero, Zero}));
    for (List<CgenNode> *cld = node->get_children(); cld != NULL; cld = cld->tl())
        llvm_code_class_name(cld->hd(), strings);
}
void CgenClassTable::llvm_code_class_to_structs(CgenNodeP node)
{

    std::vector<llvm::Type *> classFields;
    auto structType = node->get_struct_type();
    auto vtable = node->get_vtable();

    // Class Tag
    classFields.push_back(builder.get()->getInt32Ty());
    // Object Size
    classFields.push_back(builder.get()->getInt32Ty());
    // Dispatch ptr
    classFields.push_back(vtable->getPointerTo());
    std::vector<llvm::Type *> vtableFields;

    for (auto &name : node->methods)
        vtableFields.push_back(module->getFunction(name.second->get_string() + (std::string) "." + name.first->get_string())->getType());

    vtable->setBody(vtableFields);

    Symbol className = node->get_name();
    if (className->equal_string("Int", 3))
    {
        classFields.push_back(builder.get()->getInt32Ty());
    }
    else if (className->equal_string("Bool", 4))
    {
        classFields.push_back(builder.get()->getInt1Ty());
    }
    else if (className->equal_string("String", 6))
    {
        // attr: val
        classFields.push_back(get_llvm_type(Int, Int));
        // attr: str_field
        classFields.push_back(builder.get()->getInt8PtrTy());
    }
    else
    {
        int index = 0;
        for (vecFeatureIter Iter = node->attributes.begin();
             Iter != node->attributes.end(); ++Iter)
        {

            node->set_llvm_atrr_offset((*Iter)->get_name(), index);
            classFields.push_back(get_llvm_type((*Iter)->get_type(), className));
            index++;
        }
    }

    structType->setBody(classFields);

    for (List<CgenNode> *cld = node->get_children(); cld != NULL; cld = cld->tl())
        llvm_code_class_to_structs(cld->hd());
}
void CgenClassTable::llvm_code_prototype_objects(CgenNodeP node)
{

    std::string className = node->get_name()->get_string();

    Features fs = node->get_features();

    llvm::StructType *currStructType = node->get_struct_type();

    // Create function which will initialize class.
    llvm::FunctionType *classInitType = llvm::FunctionType::get(builder->getVoidTy(), currStructType->getPointerTo(), false);

    llvm::Function *classInit = llvm::Function::Create(classInitType, llvm::Function::ExternalLinkage, className + CLASSINIT_SUFFIX, module.get());

    for (List<CgenNode> *cld = node->get_children(); cld != NULL; cld = cld->tl())
        llvm_code_prototype_objects(cld->hd());
}
void CgenClassTable::llvm_code_dispatch_tables(CgenNodeP node)
{
    std::vector<llvm::Constant *> functions;
    auto vtable = node->get_vtable();

    for (vecNameNameIter Iter = node->methods.begin();
         Iter != node->methods.end(); ++Iter)
    {

        auto function = module.get()->getFunction((*Iter).second->get_string() + (std::string) "." + (*Iter).first->get_string());

        functions.push_back(function);
    }
    llvm::Constant *vtableInit = llvm::ConstantStruct::get(vtable, functions);
    new llvm::GlobalVariable(*module.get(), vtable, true, llvm::GlobalValue::ExternalLinkage, vtableInit, (std::string)node->get_name()->get_string() + DISPTAB_SUFFIX);
    for (List<CgenNode> *cld = node->get_children(); cld != NULL; cld = cld->tl())
        llvm_code_dispatch_tables(cld->hd());
}
void CgenClassTable::llvm_code_object_initializers(CgenNodeP node)
{

    llvm_tmp_table.enterscope();
    cur_node = node;

    std::string className = node->get_name()->get_string();

    Features fs = node->get_features();

    llvm::StructType *currStructType = node->get_struct_type();

    llvm::AllocaInst *classInstance = nullptr;
    llvm::ArrayRef<llvm::Type *> structFields = currStructType->elements();

    llvm::Function *classInit = module->getFunction(className + CLASSINIT_SUFFIX);

    llvm::BasicBlock *entry = llvm::BasicBlock::Create(*ctx.get(), "entry", classInit);
    builder->SetInsertPoint(entry);

    llvm::Function *malloc = module->getFunction("malloc");

    llvm::Value *ptrToStruct = classInit->getArg(0);

    llvm::Value *tag_ptr = builder->CreateStructGEP(currStructType, ptrToStruct, TAG_OFFSET, "classTag");
    builder->CreateStore(builder->getInt32(node->tag), tag_ptr);

    llvm::Value *size_ptr = builder->CreateStructGEP(currStructType, ptrToStruct, SIZE_OFFSET, "classSize");
    builder->CreateStore(builder->getInt32(DEFAULT_OBJFIELDS + node->attributes.size()), size_ptr);

    llvm::Value *dispatch_ptr = builder->CreateStructGEP(currStructType, ptrToStruct, DISPTABLE_OFFSET, "dispatchTable");
    builder->CreateStore(module->getGlobalVariable((std::string)node->get_name()->get_string() + DISPTAB_SUFFIX), dispatch_ptr);

    if (className == "Int")
    {
        llvm::Value *ptr = builder->CreateStructGEP(currStructType, ptrToStruct, 0 + DEFAULT_OBJFIELDS, "integer");
        builder->CreateStore(builder->getInt32(0), ptr);
    }
    else if (className == "Bool")
    {
        llvm::Value *ptr = builder->CreateStructGEP(currStructType, ptrToStruct, 0 + DEFAULT_OBJFIELDS, "bool");
        builder->CreateStore(builder->getInt1(0), ptr);
    }
    else if (className == "String")
    {
        llvm::Value *length_field = builder->CreateStructGEP(currStructType, ptrToStruct, 0 + DEFAULT_OBJFIELDS, "length");
        llvm::Value *intClassInstance = get_primitive(Int, builder, module, builder->getInt32(0));

        // auto load_int = builder->CreateLoad(intClassInstance->getType()->getPointerElementType(), intClassInstance);
        builder->CreateStore(intClassInstance, length_field);

        llvm::Value *str_field = builder->CreateStructGEP(currStructType, ptrToStruct, 1 + DEFAULT_OBJFIELDS, "string");
        llvm::Value *emptyStr = builder->CreateGlobalStringPtr("", "emptyStr");
        builder->CreateStore(emptyStr, str_field);
    }
    else
    {
        int index = 0;

        for (vecFeatureIter Iter = node->attributes.begin();
             Iter != node->attributes.end(); ++Iter)
        {
            llvm::Value *ptr = builder->CreateStructGEP(currStructType, ptrToStruct, index + DEFAULT_OBJFIELDS, (*Iter)->get_name()->get_string());

            index++;

            Expression expr = (*Iter)->get_expr();
            std::string attr_type = (*Iter)->get_type()->get_string();
            if ((attr_type == "Bool" || attr_type == "String" || attr_type == "Int"))
            {

                int classSize = attr_type == "Int" ? 20 : attr_type == "String" ? 32
                                                                                : 17;
                llvm::Value *mallocCall = builder->CreateCall(malloc, builder->getInt32(classSize));
                llvm::Value *newPrimitive = builder->CreateBitCast(mallocCall, get_llvm_type((*Iter)->get_type(), (*Iter)->get_type()));

                builder->CreateCall(module->getFunction(attr_type + CLASSINIT_SUFFIX), newPrimitive);
                builder->CreateStore(newPrimitive, ptr);
            }
            else if (expr->is_no_expr())
                builder->CreateStore(llvm::Constant::getNullValue(ptr->getType()->getPointerElementType()), ptr);
        }
        index = 0;
        for (vecFeatureIter Iter = node->attributes.begin();
             Iter != node->attributes.end(); ++Iter)
        {
            llvm_tmp_table.enterscope();
            Expression expr = (*Iter)->get_expr();
            if (expr->is_no_expr())
            {
                index++;
                continue;
            }
            llvm::Value *ptr = builder->CreateStructGEP(currStructType, ptrToStruct, index + DEFAULT_OBJFIELDS, (*Iter)->get_name()->get_string());

            index++;

            auto bar = new llvm::Value *(ptrToStruct);
            llvm_tmp_table.addid(self, bar);
            llvm::Value *attribute = expr->llvm_code(builder, module);

            builder->CreateStore(attribute, ptr);

            llvm_tmp_table.exitscope();
        }
    }
    // Return void
    builder->CreateRet(nullptr);
    for (List<CgenNode> *cld = node->get_children(); cld != NULL; cld = cld->tl())
        llvm_code_object_initializers(cld->hd());
}
void CgenClassTable::llvm_code_class_methods(CgenNodeP node)
{
    std::string className = node->get_name()->get_string();

    llvm::StructType *currStructType = node->get_struct_type();

    Features fs = node->get_features();

    for (vecNameNameIter Iter = node->methods.begin();
         Iter != node->methods.end(); ++Iter)
    {

        Feature_class *f = nullptr;
        for (int i = fs->first(); fs->more(i); i = fs->next(i))
        {
            Feature_class *foo = fs->nth(i);

            if (foo->is_method() && foo->get_name()->equal_string((*Iter).first->get_string(), (*Iter).first->get_len()))
            {
                f = foo;
                break;
            }
        }
        std::string method_name = (*Iter).second->get_string() + (std::string) "." + (*Iter).first->get_string();

        // If we didn't found method, it means that it was inherited but not overriden. So we just continue because method is already defined.
        if (f == nullptr)
        {
            continue;
        }

        method_class *f_method = dynamic_cast<method_class *>(f);
        std::vector<llvm::Type *>
            llvm_args;

        llvm_args.push_back(currStructType->getPointerTo());

        Formals fms = f_method->get_formals();
        for (int i = fms->first(); fms->more(i); i = fms->next(i))
        {
            formal_class *formal_param = (formal_class *)fms->nth(i);
            // llvm_args.push_back(get_llvm_type(formal_param->get_type_decl(), node->get_name())->getPointerElementType());
            llvm_args.push_back(get_llvm_type(formal_param->get_type_decl(), node->get_name()));
        }

        llvm::FunctionType *currFunctionType = llvm::FunctionType::get(get_llvm_type(f_method->return_type, node->get_name()), llvm_args, false);
        llvm::Function *currFunction = llvm::Function::Create(currFunctionType, llvm::Function::ExternalLinkage, method_name, module.get());
        auto it = currFunction->arg_begin(); // Get the iterator to the first argument
        auto end = currFunction->arg_end();  // Get the iterator to the end of the arguments

        if (it != end)
            ++it; // Skip the first argument since it pointer to struct.

        for (; it != end; ++it)
            it->addAttr(llvm::Attribute::getWithByValType(*ctx, it->getType()->getPointerElementType()));

        llvm::BasicBlock *entry = llvm::BasicBlock::Create(*ctx, "entry", currFunction);
        builder->SetInsertPoint(entry);

        if (className == "Main" && f_method->get_name()->equal_string("main", 4))
        {
            // Since LLVM requires function called main to be entry point, create it and call Main.main function.

            llvm::FunctionType *mainFunctionType = llvm::FunctionType::get(builder->getVoidTy(), false);

            llvm::Function *mainFunction = llvm::Function::Create(
                mainFunctionType, llvm::Function::ExternalLinkage, "main", module.get());

            // llvm::FunctionType *addFunctionType = llvm::FunctionType::get(
            //     builder->getInt32Ty(), {builder->getInt32Ty(), builder->getInt32Ty()}, false);

            // llvm::Function *addFunction = llvm::Function::Create(
            //     addFunctionType, llvm::Function::ExternalLinkage, "add", module.get());
            // llvm::BasicBlock *entryAdd = llvm::BasicBlock::Create(*ctx.get(), "entry", addFunction);
            // builder->SetInsertPoint(entryAdd);

            // llvm::Value *arg1 = addFunction->getArg(0);
            // llvm::Value *arg2 = addFunction->getArg(1);
            // llvm::Value *res = builder->CreateAdd(arg1, arg2);
            // builder->CreateRet(res);

            llvm::BasicBlock *entry = llvm::BasicBlock::Create(*ctx.get(), "entry", mainFunction);
            builder->SetInsertPoint(entry);
            // Allocate main class and call init function.

            llvm::Function *malloc = module->getFunction("malloc");
            llvm::Function *dump = module->getFunction("printf");
            llvm::Value *mallocCall = builder->CreateCall(malloc, builder->getInt32(256));
            llvm::Value *mainClass = builder->CreateBitCast(mallocCall, currStructType->getPointerTo());
            // llvm::AllocaInst *classInstance = builder->CreateAlloca(currStructType, nullptr);
            llvm::Function *classInit = module->getFunction(className + CLASSINIT_SUFFIX);

            builder->CreateCall(classInit, mainClass);
            builder->CreateCall(currFunction, mainClass);
            builder->CreateCall(dump, builder->CreateGlobalStringPtr("COOL program successfully executed\n", "success_msg"));
            builder->CreateRet(nullptr);
            llvm::verifyFunction(*mainFunction);
        }

        currFunction->getArg(0)->setName("self");
    }

    for (List<CgenNode> *cld = node->get_children(); cld != NULL; cld = cld->tl())
        llvm_code_class_methods(cld->hd());
}
void CgenClassTable::code_abort()
{
    llvm::Function *abort_fn = module->getFunction("Object.abort");
    llvm::BasicBlock *entry = &abort_fn->getEntryBlock();
    builder->SetInsertPoint(entry);

    llvm::Function *type_name_fn = module->getFunction("Object.type_name");
    llvm::Function *obj_init = module->getFunction("Object" + (std::string)CLASSINIT_SUFFIX);
    llvm::Function *printf = module->getFunction("printf");
    llvm::Function *exit = module->getFunction("exit");
    llvm::Function *malloc = module->getFunction("malloc");
    auto type_name = builder->CreateCall(type_name_fn, abort_fn->getArg(0));
    auto abort_spec = builder->CreateGlobalStringPtr("%s %s\n", "abort_format");
    auto abort_msg = builder->CreateGlobalStringPtr("Abort called from class", "abort_msg");
    auto className = builder->CreateStructGEP(type_name->getType()->getPointerElementType(), type_name, 1 + DEFAULT_OBJFIELDS);
    builder->CreateCall(printf, {abort_spec, abort_msg, builder->CreateLoad(className->getType()->getPointerElementType(), className)});
    auto init_obj = module->getFunction((std::string) "Object" + CLASSINIT_SUFFIX);
    builder->CreateCall(exit, builder->getInt32(1));
    llvm::Value *mallocCall = builder->CreateCall(malloc, builder->getInt32(256));
    llvm::Value *new_obj = builder->CreateBitCast(mallocCall, obj_init->getArg(0)->getType());
    builder->CreateCall(obj_init, new_obj);

    builder->CreateRet(new_obj);
    llvm::verifyFunction(*abort_fn);
}
void CgenClassTable::code_type_name()
{
    llvm::Function *type_name_fn = module->getFunction("Object.type_name");
    llvm::BasicBlock *entry = &type_name_fn->getEntryBlock();
    builder->SetInsertPoint(entry);
    auto selfptr = type_name_fn->getArg(0);
    auto offset = builder->CreateStructGEP(selfptr->getType()->getPointerElementType(), selfptr, TAG_OFFSET);
    auto loaded_offset = builder->CreateLoad(offset->getType()->getPointerElementType(), offset);
    auto strArray = module->getNamedGlobal(".str_array");
    llvm::Value *GEP1 = builder->CreateInBoundsGEP(strArray->getValueType(), strArray, {builder->getInt32(0), loaded_offset});
    llvm::Value *Load1 = builder->CreateLoad(GEP1->getType()->getPointerElementType(), GEP1);
    auto strClassInst = get_primitive(Str, builder, module, Load1);

    llvm::Function *strlen = module->getFunction("strlen");
    auto new_length = builder->CreateCall(strlen, Load1);
    llvm::Value *length_field = builder->CreateStructGEP(strClassInst->getType()->getPointerElementType(), strClassInst, 0 + DEFAULT_OBJFIELDS);

    auto loaded_field = builder->CreateLoad(length_field->getType()->getPointerElementType(), length_field);
    builder->CreateStore(new_length, builder->CreateStructGEP(loaded_field->getType()->getPointerElementType(), loaded_field, 0 + DEFAULT_OBJFIELDS));

    builder->CreateRet(strClassInst);
    llvm::verifyFunction(*type_name_fn);
}
void CgenClassTable::code_copy()
{
    llvm::Function *copy_fn = module->getFunction("Object.copy");
    llvm::BasicBlock *entry = &copy_fn->getEntryBlock();
    builder->SetInsertPoint(entry);

    llvm::Function *memcpy = module->getFunction("memcpy");
    llvm::Function *malloc = module->getFunction("malloc");

    auto malloc_call = builder->CreateCall(malloc, builder->getInt32(256));
    auto self_to_i8 = builder->CreateBitCast(copy_fn->getArg(0), builder->getInt8PtrTy());
    builder->CreateCall(memcpy, {malloc_call, self_to_i8, builder->getInt32(256)});
    auto newClass = builder->CreateBitCast(malloc_call, copy_fn->getArg(0)->getType());
    builder->CreateRet(newClass);
    llvm::verifyFunction(*copy_fn);
}
void CgenClassTable::code_out_string()
{
    llvm::Function *out_string_fn = module->getFunction("IO.out_string");
    llvm::BasicBlock *entry = &out_string_fn->getEntryBlock();
    builder->SetInsertPoint(entry);

    llvm::Value *self = out_string_fn->getArg(0);
    llvm::Value *string_to_print = out_string_fn->getArg(1);

    llvm::Function *printf = module->getFunction("printf");

    string_to_print = builder->CreateStructGEP(string_to_print->getType()->getPointerElementType(), string_to_print, 1 + DEFAULT_OBJFIELDS);
    llvm::Value *printf_call = builder->CreateCall(printf, builder->CreateLoad(string_to_print->getType()->getPointerElementType(), string_to_print));
    builder->CreateRet(self);
    llvm::verifyFunction(*out_string_fn);
}
void CgenClassTable::code_out_int()
{
    llvm::Function *out_int_fn = module->getFunction("IO.out_int");
    llvm::BasicBlock *entry = &out_int_fn->getEntryBlock();
    builder->SetInsertPoint(entry);

    llvm::Value *self = out_int_fn->getArg(0);
    llvm::Value *int_to_print = out_int_fn->getArg(1);

    llvm::Function *printf = module->getFunction("printf");
    llvm::Value *format_int = builder->CreateGlobalStringPtr("%d", "format_int");
    int_to_print = builder->CreateStructGEP(int_to_print->getType()->getPointerElementType(), int_to_print, 0 + DEFAULT_OBJFIELDS);
    llvm::Value *printf_call = builder->CreateCall(printf, {format_int, builder->CreateLoad(int_to_print->getType()->getPointerElementType(), int_to_print)});

    builder->CreateRet(self);
    llvm::verifyFunction(*out_int_fn);
}

void CgenClassTable::code_in_string()
{
    llvm::Function *in_string_fn = module->getFunction("IO.in_string");
    llvm::BasicBlock *entry = &in_string_fn->getEntryBlock();
    builder->SetInsertPoint(entry);

    llvm::Value *self = in_string_fn->getArg(0);

    llvm::Function *scanf = module->getFunction("scanf");
    llvm::Function *malloc = module->getFunction("malloc");
    llvm::Function *strlen = module->getFunction("strlen");

    llvm::Value *bufferSize = builder->getInt32(1026);
    llvm::Value *buffer = builder->CreateAlloca(builder->getInt8Ty(), bufferSize, "buffer");
    llvm::Value *new_string = get_primitive(Str, builder, module, buffer);

    llvm::Value *new_string_str_field = builder->CreateStructGEP(new_string->getType()->getPointerElementType(), new_string, 1 + DEFAULT_OBJFIELDS);

    llvm::Value *format_string = builder->CreateGlobalStringPtr("%s", "format_string");

    llvm::Value *scanf_call = builder->CreateCall(scanf, {format_string, builder->CreateLoad(new_string_str_field->getType()->getPointerElementType(), new_string_str_field)});
    llvm::Value *strlen_call = builder->CreateCall(strlen, {builder->CreateLoad(new_string_str_field->getType()->getPointerElementType(), new_string_str_field)});

    llvm::Value *new_string_length_field = builder->CreateStructGEP(new_string->getType()->getPointerElementType(), new_string, 0 + DEFAULT_OBJFIELDS);
    auto loaded_field = builder->CreateLoad(new_string_length_field->getType()->getPointerElementType(), new_string_length_field);
    builder->CreateStore(strlen_call, builder->CreateStructGEP(loaded_field->getType()->getPointerElementType(), loaded_field, 0 + DEFAULT_OBJFIELDS));

    builder->CreateRet(new_string);
    llvm::verifyFunction(*in_string_fn);
}
void CgenClassTable::code_in_int()
{
    llvm::Function *in_int_fn = module->getFunction("IO.in_int");
    llvm::BasicBlock *entry = &in_int_fn->getEntryBlock();
    builder->SetInsertPoint(entry);

    llvm::Value *self = in_int_fn->getArg(0);
    llvm::Function *scanf = module->getFunction("scanf");

    llvm::Value *new_int = get_primitive(Int, builder, module, builder->getInt32(0));
    llvm::Value *new_int_i32_field = builder->CreateStructGEP(new_int->getType()->getPointerElementType(), new_int, 0 + DEFAULT_OBJFIELDS);
    llvm::Value *format_int = builder->CreatePointerCast(module->getNamedGlobal("format_int"), builder->getInt8PtrTy());

    llvm::Value *scanf_call = builder->CreateCall(scanf, {format_int, new_int_i32_field});

    builder->CreateRet(new_int);
    llvm::verifyFunction(*in_int_fn);
}
void CgenClassTable::code_length()
{
    llvm::Function *string_length_fn = module->getFunction("String.length");
    llvm::BasicBlock *length_entry = &string_length_fn->getEntryBlock();
    builder->SetInsertPoint(length_entry);

    llvm::Value *string_self_length = string_length_fn->getArg(0);
    llvm::Value *length_field = builder->CreateStructGEP(string_self_length->getType()->getPointerElementType(), string_self_length, 0 + DEFAULT_OBJFIELDS);
    llvm::Value *loaded_length_field = builder->CreateLoad(length_field->getType()->getPointerElementType(), length_field);
    builder->CreateRet(loaded_length_field);

    llvm::verifyFunction(*string_length_fn);
}

void CgenClassTable::code_concat()
{
    llvm::Function *string_concat_fn = module->getFunction("String.concat");
    llvm::BasicBlock *concat_entry = &string_concat_fn->getEntryBlock();
    builder->SetInsertPoint(concat_entry);

    llvm::Value *string_self_concat = string_concat_fn->getArg(0);
    llvm::Value *str_field_self = builder->CreateStructGEP(string_self_concat->getType()->getPointerElementType(), string_self_concat, 1 + DEFAULT_OBJFIELDS);
    llvm::Value *s = string_concat_fn->getArg(1);

    llvm::Value *bar = builder->CreateStructGEP(string_self_concat->getType()->getPointerElementType(), string_self_concat, 0 + DEFAULT_OBJFIELDS);

    llvm::Value *baz = builder->CreateLoad(bar->getType()->getPointerElementType(), bar);
    llvm::Value *foo = builder->CreateStructGEP(baz->getType()->getPointerElementType(), baz, 0 + DEFAULT_OBJFIELDS);

    llvm::Value *self_string_length = builder->CreateLoad(foo->getType()->getPointerElementType(), foo);

    llvm::Value *s_string_length = builder->CreateStructGEP(s->getType()->getPointerElementType(), s, 0 + DEFAULT_OBJFIELDS);
    s_string_length = builder->CreateLoad(s_string_length->getType()->getPointerElementType(), s_string_length);

    llvm::Value *s_string_length_i32 = builder->CreateStructGEP(s_string_length->getType()->getPointerElementType(), s_string_length, 0 + DEFAULT_OBJFIELDS);
    s_string_length_i32 = builder->CreateLoad(s_string_length_i32->getType()->getPointerElementType(), s_string_length_i32);

    llvm::Value *new_length_value = builder->CreateAdd(
        self_string_length, s_string_length_i32);

    llvm::Function *malloc = module->getFunction("malloc");
    llvm::Value *malloc_call = builder->CreateCall(malloc, new_length_value);

    llvm::Function *memcpy = module->getFunction("memcpy");
    builder->CreateCall(memcpy, {malloc_call, builder->CreateLoad(str_field_self->getType()->getPointerElementType(), str_field_self), self_string_length});

    llvm::Value *EndOfFirstStr = builder->CreateGEP(malloc_call->getType()->getPointerElementType(), malloc_call, self_string_length, "endOfFirstStr");

    // Copy the second string to the new allocated space, starting after the first string
    auto s_str_field = builder->CreateStructGEP(s->getType()->getPointerElementType(), s, 1 + DEFAULT_OBJFIELDS);
    s_str_field = builder->CreateLoad(s_str_field->getType()->getPointerElementType(), s_str_field);
    builder->CreateCall(memcpy, {EndOfFirstStr, s_str_field, s_string_length_i32});
    llvm::Value *new_string = get_primitive(Str, builder, module, malloc_call);

    llvm::Value *new_string_length_field = builder->CreateStructGEP(new_string->getType()->getPointerElementType(), new_string, 0 + DEFAULT_OBJFIELDS);
    auto loaded_field = builder->CreateLoad(new_string_length_field->getType()->getPointerElementType(), new_string_length_field);
    builder->CreateStore(new_length_value, builder->CreateStructGEP(loaded_field->getType()->getPointerElementType(), loaded_field, 0 + DEFAULT_OBJFIELDS));

    builder->CreateRet(new_string);
    cout << "7.4\n";
    llvm::verifyFunction(*string_concat_fn);
}
void CgenClassTable::code_substring()
{
    llvm::Function *string_substring_fn = module->getFunction("String.substr");
    llvm::BasicBlock *entry = &string_substring_fn->getEntryBlock();
    builder->SetInsertPoint(entry);

    llvm::Value *string_self = string_substring_fn->getArg(0);
    llvm::Value *str_field_self = builder->CreateStructGEP(string_self->getType()->getPointerElementType(), string_self, 1 + DEFAULT_OBJFIELDS);
    llvm::Value *index = string_substring_fn->getArg(1);
    llvm::Value *length = string_substring_fn->getArg(2);

    llvm::Value *new_length_value = builder->CreateStructGEP(length->getType()->getPointerElementType(), length, 0 + DEFAULT_OBJFIELDS);
    new_length_value = builder->CreateLoad(new_length_value->getType()->getPointerElementType(), new_length_value);
    llvm::Function *malloc = module->getFunction("malloc");
    llvm::Value *malloc_call = builder->CreateCall(malloc, new_length_value);

    llvm::Function *memcpy = module->getFunction("memcpy");
    llvm::Value *load_str_field_self = builder->CreateLoad(str_field_self->getType()->getPointerElementType(), str_field_self);
    index = builder->CreateStructGEP(index->getType()->getPointerElementType(), index, 0 + DEFAULT_OBJFIELDS);
    index = builder->CreateLoad(index->getType()->getPointerElementType(), index);
    llvm::Value *string_at_index = builder->CreateGEP(load_str_field_self->getType()->getPointerElementType(), load_str_field_self, index, "string_at_index");

    builder->CreateCall(memcpy, {malloc_call, string_at_index, new_length_value});

    llvm::Value *new_string = get_primitive(Str, builder, module, malloc_call);

    llvm::Value *new_string_length_field = builder->CreateStructGEP(new_string->getType()->getPointerElementType(), new_string, 0 + DEFAULT_OBJFIELDS);
    auto loaded_field = builder->CreateLoad(new_string_length_field->getType()->getPointerElementType(), new_string_length_field);
    builder->CreateStore(new_length_value, builder->CreateStructGEP(loaded_field->getType()->getPointerElementType(), loaded_field, 0 + DEFAULT_OBJFIELDS));

    builder->CreateRet(new_string);
    llvm::verifyFunction(*string_substring_fn);
}
// TODO: llvm code
void CgenClassTable::llvm_code_class(CgenNodeP node, std::ofstream *out)
{
    node->dump_with_types(*out, 0);

    std::string className = node->get_name()->get_string();
    cout << "Classname: " << className << endl;

    llvm::StructType *currStructType = node->get_struct_type();

    llvm::Value *res = nullptr;
    Features fs = node->get_features();

    if (node->basic() == false)
    {
        for (vecNameNameIter Iter = node->methods.begin();
             Iter != node->methods.end(); ++Iter)
        {

            Feature_class *f = nullptr;
            for (int i = fs->first(); fs->more(i); i = fs->next(i))
            {
                Feature_class *foo = fs->nth(i);

                if (foo->is_method() && foo->get_name()->equal_string((*Iter).first->get_string(), (*Iter).first->get_len()))
                {
                    f = foo;
                    break;
                }
            }
            // If we didn't found method, it means that it was inherited but not overriden. So we just continue because method is already defined.
            if (f == nullptr)
            {
                continue;
            }
            method_class *f_method = dynamic_cast<method_class *>(f);
            cur_node = node;
            std::string method_name = (*Iter).second->get_string() + (std::string) "." + (*Iter).first->get_string();

            llvm::Function *currFunction = module->getFunction(method_name);
            llvm::BasicBlock *entry = &currFunction->getEntryBlock();
            builder->SetInsertPoint(entry);

            llvm_tmp_table.enterscope();

            Formals fms = f_method->get_formals();
            auto it = currFunction->arg_begin(); // Get the iterator to the first argument
            auto end = currFunction->arg_end();  // Get the iterator to the end of the arguments

            if (it != end)
            {
                ++it; // Skip the first argument since it pointer to struct.
            }

            int index = 0;
            for (; it != end; ++it)
            {
                formal_class *formal_param = (formal_class *)fms->nth(index);
                // llvm::Value *stackClass = builder->CreateAlloca(currFunction->getArg(index + 1)->getType());
                // builder->CreateStore(currFunction->getArg(index + 1), stackClass);
                // it->addAttr(llvm::Attribute::ByVal);

                auto bar = new llvm::Value *(it);
                llvm_tmp_table.addid(formal_param->get_name(), bar);
                index++;
            }
            res = f_method->get_expr()->llvm_code(builder, module);

            if (res != nullptr)
            {
                cout << "Res:" << endl;

                if (res->getType()->getPointerElementType()->isPointerTy())
                {
                    res = builder->CreateLoad(res->getType()->getPointerElementType(), res);
                }
                if (res->getType() != currFunction->getReturnType())
                {
                    res = builder->CreateBitCast(res, currFunction->getReturnType());
                }

                builder->CreateRet(res);
                res = nullptr;
            }

            llvm::verifyFunction(*currFunction);
            llvm_tmp_table.exitscope();
        }
    }

    for (List<CgenNode> *cld = node->get_children(); cld != NULL; cld = cld->tl())
        llvm_code_class(cld->hd(), out);
}

void CgenClassTable::install_basic_classes()
{

    // The tree package uses these globals to annotate the classes built below.
    // curr_lineno  = 0;
    Symbol filename = stringtable.add_string("<basic class>");

    //
    // A few special class names are installed in the lookup table but not
    // the class list.  Thus, these classes exist, but are not part of the
    // inheritance hierarchy.
    // No_class serves as the parent of Object and the other special classes.
    // SELF_TYPE is the self class; it cannot be redefined or inherited.
    // prim_slot is a class known to the code generator.
    //
    addid(No_class,
          new CgenNode(class_(No_class, No_class, nil_Features(), filename),
                       Basic, this));
    addid(SELF_TYPE,
          new CgenNode(class_(SELF_TYPE, No_class, nil_Features(), filename),
                       Basic, this));
    addid(prim_slot,
          new CgenNode(class_(prim_slot, No_class, nil_Features(), filename),
                       Basic, this));

    //
    // The Object class has no parent class. Its methods are
    //        cool_abort() : Object    aborts the program
    //        type_name() : Str        returns a string representation of class name
    //        copy() : SELF_TYPE       returns a copy of the object
    //
    // There is no need for method bodies in the basic classes---these
    // are already built in to the runtime system.
    //
    install_class(
        new CgenNode(
            class_(Object,
                   No_class,
                   append_Features(
                       append_Features(
                           single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
                           single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
                       single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
                   filename),
            Basic, this));

    //
    // The IO class inherits from Object. Its methods are
    //        out_string(Str) : SELF_TYPE          writes a string to the output
    //        out_int(Int) : SELF_TYPE               "    an int    "  "     "
    //        in_string() : Str                    reads a string from the input
    //        in_int() : Int                         "   an int     "  "     "
    //
    install_class(
        new CgenNode(
            class_(IO,
                   Object,
                   append_Features(
                       append_Features(
                           append_Features(
                               single_Features(method(out_string, single_Formals(formal(arg, Str)),
                                                      SELF_TYPE, no_expr())),
                               single_Features(method(out_int, single_Formals(formal(arg, Int)),
                                                      SELF_TYPE, no_expr()))),
                           single_Features(method(in_string, nil_Formals(), Str, no_expr()))),
                       single_Features(method(in_int, nil_Formals(), Int, no_expr()))),
                   filename),
            Basic, this));

    //
    // The Int class has no methods and only a single attribute, the
    // "val" for the integer.
    //
    install_class(
        new CgenNode(
            class_(Int,
                   Object,
                   single_Features(attr(val, prim_slot, no_expr())),
                   filename),
            Basic, this));

    //
    // Bool also has only the "val" slot.
    //
    install_class(
        new CgenNode(
            class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())), filename),
            Basic, this));

    //
    // The class Str has a number of slots and operations:
    //       val                                  ???
    //       str_field                            the string itself
    //       length() : Int                       length of the string
    //       concat(arg: Str) : Str               string concatenation
    //       substr(arg: Int, arg2: Int): Str     substring
    //
    install_class(
        new CgenNode(
            class_(Str,
                   Object,
                   append_Features(
                       append_Features(
                           append_Features(
                               append_Features(
                                   single_Features(attr(val, Int, no_expr())),
                                   single_Features(attr(str_field, prim_slot, no_expr()))),
                               single_Features(method(length, nil_Formals(), Int, no_expr()))),
                           single_Features(method(concat,
                                                  single_Formals(formal(arg, Str)),
                                                  Str,
                                                  no_expr()))),
                       single_Features(method(substr,
                                              append_Formals(single_Formals(formal(arg, Int)),
                                                             single_Formals(formal(arg2, Int))),
                                              Str,
                                              no_expr()))),
                   filename),
            Basic, this));
}

// CgenClassTable::install_class
// CgenClassTable::install_classes
//
// install_classes enters a list of classes in the symbol table.
void CgenClassTable::install_class(CgenNodeP nd)
{
    Symbol name = nd->get_name();

    if (probe(name))
    {
        return;
    }

    // The class name is legal, so add it to the list of classes
    // and the symbol table.
    nds = new List<CgenNode>(nd, nds);

    llvm::StructType *currStructType = llvm::StructType::create(*ctx.get(), name->get_string());
    llvm::StructType *vTable = llvm::StructType::create(*ctx.get(), (std::string)name->get_string() + DISPTAB_SUFFIX);
    builder->CreateGlobalString(name->get_string(), name->get_string(), 0, module.get());

    nd->set_struct_type(currStructType);
    nd->set_vtable(vTable);
    addid(name, nd);
}

void CgenClassTable::install_classes(Classes cs)
{
    for (int i = cs->first(); cs->more(i); i = cs->next(i))
        install_class(new CgenNode(cs->nth(i), NotBasic, this));
}

//
// CgenClassTable::build_inheritance_tree
//
void CgenClassTable::build_inheritance_tree()
{
    for (List<CgenNode> *l = nds; l; l = l->tl())
        set_relations(l->hd());
}

//
// CgenClassTable::set_relations
//
// Takes a CgenNode and locates its, and its parent's, inheritance nodes
// via the class table.  Parent and child pointers are added as appropriate.
//
void CgenClassTable::set_relations(CgenNodeP nd)
{
    CgenNode *parent_node = probe(nd->get_parent());
    nd->set_parentnd(parent_node);
    parent_node->add_child(nd);
}

void CgenNode::add_child(CgenNodeP n)
{
    children = new List<CgenNode>(n, children);
}

void CgenNode::set_parentnd(CgenNodeP p)
{
    assert(parentnd == NULL);
    assert(p != NULL);
    parentnd = p;
}

// Vecina koda ispod je novo.

void CgenClassTable::code_fill_features(CgenNodeP node)
{
    // from parent
    if (node->get_name() != Object)
    {
        CgenNodeP pnode = node->get_parentnd();
        for (vecNameNameIter Iter = pnode->methods.begin();
             Iter != pnode->methods.end(); ++Iter)
            node->methods.push_back(*Iter);
        for (vecFeatureIter Iter = pnode->attributes.begin();
             Iter != pnode->attributes.end(); ++Iter)
            node->attributes.push_back(*Iter);
    }
    Features fs = node->get_features();
    for (int i = fs->first(); fs->more(i); i = fs->next(i))
    {
        Feature_class *f = fs->nth(i);
        if (f->is_method())
        {
            // override?
            bool found = false;
            for (vecNameNameIter Iter = node->methods.begin();
                 Iter != node->methods.end(); ++Iter)
                if (Iter->first == f->get_name())
                {
                    Iter->second = node->get_name();
                    found = true;
                }
            if (found == false)
                node->methods.push_back(
                    std::make_pair(f->get_name(), node->get_name()));
        }
        else
            node->attributes.push_back(f);
    }
    for (List<CgenNode> *cld = node->get_children(); cld != NULL; cld = cld->tl())
        code_fill_features(cld->hd());
}

// TODO: code
void CgenClassTable::code()
{

    if (cgen_debug)
        cout << "coding - filling class features" << endl;
    code_fill_features(root());
}

CgenNodeP CgenClassTable::root()
{
    return probe(Object);
}

///////////////////////////////////////////////////////////////////////
//
// CgenNode methods
//
///////////////////////////////////////////////////////////////////////

CgenNode::CgenNode(Class_ nd, Basicness bstatus, CgenClassTableP ct) : class__class((const class__class &)*nd),
                                                                       parentnd(NULL),
                                                                       children(NULL),
                                                                       basic_status(bstatus)
{
    stringtable.add_string(name->get_string()); // Add class name to string table
    tag = 0;
}

int CgenNode::get_meth_offset(Symbol meth_name)
{
    // in disptable
    int offset = 0;
    for (vecNameNameIter Iter = this->methods.begin();
         Iter != this->methods.end(); ++Iter)
    {
        if ((*Iter).first == meth_name)
            return offset;
        else
            ++offset;
    }
    return -1; // not found
}

//******************************************************************
//
//   Fill in the following methods to produce code for the
//   appropriate expression.  You may add or remove parameters
//   as you wish, but if you do, remember to change the parameters
//   of the declarations in `cool-tree.h'  Sample code for
//   constant integers, strings, and booleans are provided.
//
//*****************************************************************
llvm::Value *assign_class::llvm_code(Builder &builder, Module &module)
{
    // cout << "Assign begin\n";
    llvm::Value *rhs_expr = expr->llvm_code(builder, module);
    auto offset = llvm_lookup_var(name);
    llvm::Function *fn = builder->GetInsertBlock()->getParent();
    // cout << "name: " << name << endl;

    if (std::get<0>(offset))
    {
        // cout << "Object is attribute.\n";
        llvm::Value *id = builder->CreateStructGEP(fn->getArg(0)->getType()->getPointerElementType(), fn->getArg(0), std::get<2>(offset));
        if (rhs_expr->getType() != id->getType()->getPointerElementType())
            rhs_expr = builder->CreateBitCast(rhs_expr, id->getType()->getPointerElementType());

        builder->CreateStore(rhs_expr, id);
        // cout << "Assign done\n";

        return id;
    }
    // rhs_expr->dump();
    // if (rhs_expr->getType()->getPointerElementType()->isPointerTy())
    //     builder->CreateStore(builder->CreateLoad(rhs_expr->getType()->getPointerElementType(), rhs_expr), std::get<1>(offset));
    // else
    //     builder->CreateStore(rhs_expr, std::get<1>(offset));
    // builder->CreateStore(builder->CreateLoad(rhs_expr->getType()->getPointerElementType(), rhs_expr), std::get<1>(offset));
    // if(std::get<1>(offset)->getType()->is)
    // if (auto *loadInst = llvm::dyn_cast<llvm::LoadInst>(std::get<1>(offset)))
    // {
    //     auto originalStore = loadInst->getPointerOperand();
    //     builder->CreateStore(rhs_expr, originalStore);
    //     llvm_tmp_table.addid(name, new llvm::Value *(builder->CreateLoad(originalStore->getType()->getPointerElementType(), originalStore)));
    //     //cout << "Assign done\n";
    //     return *llvm_tmp_table.probe(name);
    //     // return std::get<1>(offset);
    // }
    // else
    // {
    //     builder->CreateStore(builder->CreateLoad(rhs_expr->getType()->getPointerElementType(), rhs_expr), std::get<1>(offset));
    //     //cout << "Assign done\n";

    //     return std::get<1>(offset);
    // }

    if (rhs_expr->getType()->isPointerTy() && !std::get<1>(offset)->getType()->getPointerElementType()->isPointerTy())
        rhs_expr = builder->CreateLoad(rhs_expr->getType()->getPointerElementType(), rhs_expr);
    if (rhs_expr->getType() != std::get<1>(offset)->getType()->getPointerElementType())
        rhs_expr = builder->CreateBitCast(rhs_expr, std::get<1>(offset)->getType()->getPointerElementType());

    builder->CreateStore(rhs_expr, std::get<1>(offset));
    if (std::get<1>(offset)->getType()->getPointerElementType()->isPointerTy())
        return builder->CreateLoad(std::get<1>(offset)->getType()->getPointerElementType(), std::get<1>(offset));

    // return std::get<1>(offset);
    auto newValue = builder->CreateAlloca(std::get<1>(offset)->getType()->getPointerElementType());
    builder->CreateStore(builder->CreateLoad(std::get<1>(offset)->getType()->getPointerElementType(), std::get<1>(offset)), newValue);
    return newValue;
}

llvm::Value *static_dispatch_class::llvm_code(Builder &builder, Module &module)
{
    int offset =
        class_table->probe(this->type_name)->get_meth_offset(this->name);

    std::vector<llvm::Value *> args;
    llvm::Function *fn = builder->GetInsertBlock()->getParent();

    llvm::Value *first_arg = expr->llvm_code(builder, module);

    // Code dispatch to void
    llvm::Value *is_null = builder->CreateIsNull(first_arg);
    llvm::BasicBlock *isVoidBlock = llvm::BasicBlock::Create(builder->getContext(), "isVoidBlock", fn);
    llvm::BasicBlock *notVoidBlock = llvm::BasicBlock::Create(builder->getContext(), "notVoidBlock");
    builder->CreateCondBr(is_null, isVoidBlock, notVoidBlock);

    fn->getBasicBlockList().push_back(isVoidBlock);
    builder->SetInsertPoint(isVoidBlock);
    auto dump = module->getFunction("printf");
    auto exit = module->getFunction("exit");
    llvm::Value *file_name = builder->CreatePointerCast(module->getNamedGlobal("file_name"), builder->getInt8PtrTy());
    llvm::Value *dispatch_msg = builder->CreatePointerCast(module->getNamedGlobal("_dispatch_msg"), builder->getInt8PtrTy());
    llvm::Value *format = builder->CreateGlobalStringPtr("%s%s%s");
    llvm::Value *linenumber = builder->CreateGlobalStringPtr((std::string) ":" + std::to_string(cur_node->get_line_number()));

    builder->CreateCall(dump, {format, file_name, linenumber, dispatch_msg});
    builder->CreateCall(exit, builder->getInt32(1));

    if (fn->getReturnType()->isVoidTy())
        builder->CreateRet(nullptr);
    else
        builder->CreateRet(llvm::Constant::getNullValue(fn->getReturnType()));
    fn->getBasicBlockList().push_back(notVoidBlock);
    builder->SetInsertPoint(notVoidBlock);
    //  End code
    llvm::Value *dispatch_table = module->getNamedGlobal(this->type_name->get_string() + (std::string)DISPTAB_SUFFIX);

    auto callee_ptr = builder->CreateStructGEP(dispatch_table->getType()->getPointerElementType(), dispatch_table, offset);

    llvm::Value *callee = builder->CreateLoad(callee_ptr->getType()->getPointerElementType(), callee_ptr, this->name->get_string());

    llvm::FunctionType *calleeType = llvm::dyn_cast<llvm::FunctionType>(callee->getType()->getPointerElementType());

    auto castedCallee = (llvm::Function *)builder->CreateBitCast(callee, llvm::PointerType::getUnqual(calleeType), this->name->get_string());

    if (calleeType->getFunctionParamType(0) != first_arg->getType())
    {
        first_arg = builder->CreateBitCast(first_arg, calleeType->getFunctionParamType(0));
    }

    args.push_back(first_arg);
    for (int i = actual->first(); actual->more(i); i = actual->next(i))
    {
        auto value = actual->nth(i)->llvm_code(builder, module);
        if (value->getType()->isPointerTy())
        {
            if (calleeType->getFunctionParamType(i + 1) != value->getType()->getPointerElementType())
            {
                value = builder->CreateBitCast(value, calleeType->getFunctionParamType(i + 1));
            }
        }

        args.push_back(value);
    }

    auto call = builder->CreateCall(calleeType, castedCallee, args);
    auto it = call->arg_begin(); // Get the iterator to the first argument
    auto end = call->arg_end();  // Get the iterator to the end of the arguments

    if (it != end)
        ++it; // Skip the first argument since it pointer to struct.

    int index = 1;
    for (; it != end; ++it)
    {

        call->addParamAttr(index, llvm::Attribute::getWithByValType(builder->getContext(), args[index]->getType()->getPointerElementType()));
        index++;
    }

    return call;
}

llvm::Value *dispatch_class::llvm_code(Builder &builder, Module &module)
{
    // cout << "Dispatch begin\n";
    // cout << "For meth: " << name->get_string() << endl;
    Symbol tp = expr->get_type();
    tp = tp == SELF_TYPE ? cur_node->get_name() : tp;
    auto node = class_table->probe(tp);
    int offset = node->get_meth_offset(this->name);

    std::vector<llvm::Value *> args;
    llvm::Function *fn = builder->GetInsertBlock()->getParent();

    llvm::Value *first_arg = expr->llvm_code(builder, module);

    // Code dispatch to void
    llvm::Value *is_null = builder->CreateIsNull(first_arg);
    llvm::BasicBlock *isVoidBlock = llvm::BasicBlock::Create(builder->getContext(), "isVoidBlock", fn);
    llvm::BasicBlock *notVoidBlock = llvm::BasicBlock::Create(builder->getContext(), "notVoidBlock");

    builder->CreateCondBr(is_null, isVoidBlock, notVoidBlock);
    fn->getBasicBlockList().push_back(isVoidBlock);
    builder->SetInsertPoint(isVoidBlock);

    auto dump = module->getFunction("printf");
    auto exit = module->getFunction("exit");
    llvm::Value *file_name = builder->CreatePointerCast(module->getNamedGlobal("file_name"), builder->getInt8PtrTy());
    llvm::Value *dispatch_msg = builder->CreatePointerCast(module->getNamedGlobal("_dispatch_msg"), builder->getInt8PtrTy());
    llvm::Value *format = builder->CreateGlobalStringPtr("%s%s%s");
    llvm::Value *linenumber = builder->CreateGlobalStringPtr((std::string) ":" + std::to_string(cur_node->get_line_number()));

    builder->CreateCall(dump, {format, file_name, linenumber, dispatch_msg});
    builder->CreateCall(exit, builder->getInt32(1));

    if (fn->getReturnType()->isVoidTy())
        builder->CreateRet(nullptr);
    else
        builder->CreateRet(llvm::Constant::getNullValue(fn->getReturnType()));

    fn->getBasicBlockList().push_back(notVoidBlock);
    builder->SetInsertPoint(notVoidBlock);
    //  End code
    llvm::Value *dispatch_table_ptr = builder->CreateStructGEP(first_arg->getType()->getPointerElementType(), first_arg, DISPTABLE_OFFSET);

    llvm::Value *dispatch_table = builder->CreateLoad(dispatch_table_ptr->getType()->getPointerElementType(), dispatch_table_ptr);

    auto callee_ptr = builder->CreateStructGEP(dispatch_table->getType()->getPointerElementType(), dispatch_table, offset);

    llvm::Value *callee = builder->CreateLoad(callee_ptr->getType()->getPointerElementType(), callee_ptr, this->name->get_string());

    llvm::FunctionType *calleeType = llvm::dyn_cast<llvm::FunctionType>(callee->getType()->getPointerElementType());

    auto castedCallee = (llvm::Function *)builder->CreateBitCast(callee, llvm::PointerType::getUnqual(calleeType), this->name->get_string());

    if (calleeType->getFunctionParamType(0) != first_arg->getType())
    {
        first_arg = builder->CreateBitCast(first_arg, calleeType->getFunctionParamType(0));
    }

    args.push_back(first_arg);
    for (int i = actual->first(); actual->more(i); i = actual->next(i))
    {
        auto value = actual->nth(i)->llvm_code(builder, module);
        if (value->getType()->isPointerTy())
        {
            if (calleeType->getFunctionParamType(i + 1) != value->getType()->getPointerElementType())
            {
                value = builder->CreateBitCast(value, calleeType->getFunctionParamType(i + 1));
            }
        }

        args.push_back(value);
    }

    auto call = builder->CreateCall(calleeType, castedCallee, args);
    auto it = call->arg_begin(); // Get the iterator to the first argument
    auto end = call->arg_end();  // Get the iterator to the end of the arguments

    if (it != end)
        ++it; // Skip the first argument since it pointer to struct.

    int index = 1;
    for (; it != end; ++it)
    {

        call->addParamAttr(index, llvm::Attribute::getWithByValType(builder->getContext(), args[index]->getType()->getPointerElementType()));
        index++;
    }

    return call;
}

llvm::Value *cond_class::llvm_code(Builder &builder, Module &module)
{
    // cout << "IF start\n";
    llvm::Function *fn = builder->GetInsertBlock()->getParent();
    llvm::BasicBlock *thenBlock = llvm::BasicBlock::Create(builder->getContext(), "thenBlock", fn);
    llvm::BasicBlock *elseBlock = llvm::BasicBlock::Create(builder->getContext(), "elseBlock");
    llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(builder->getContext(), "mergeBlock");

    llvm::Value *pred_val = pred->llvm_code(builder, module);

    llvm::Type *phiType = nullptr;

    if (then_exp->get_type() != else_exp->get_type())
    {
        auto node1 = then_exp->get_type() == SELF_TYPE ? cur_node : class_table->probe(then_exp->get_type());
        auto node2 = else_exp->get_type() == SELF_TYPE ? cur_node : class_table->probe(else_exp->get_type());
        Symbol commonType = get_lub(node1, node2);

        phiType = get_llvm_type(commonType, commonType);
    }
    // pred_val->dump();

    // maybe or maybe not neccessary.
    //  CondV = Builder->CreateFCmpONE(
    //    CondV, ConstantFP::get(*TheContext, APFloat(0.0)), "ifcond");
    if (pred_val->getType() != builder->getInt1Ty())
    {
        llvm::Value *ptr_to_bool = builder->CreateStructGEP(pred_val->getType()->getPointerElementType(), pred_val, 0 + DEFAULT_OBJFIELDS);
        pred_val = builder->CreateLoad(ptr_to_bool->getType()->getPointerElementType(), ptr_to_bool);
    }
    builder->CreateCondBr(pred_val, thenBlock, elseBlock);

    fn->getBasicBlockList().push_back(thenBlock);
    builder->SetInsertPoint(thenBlock);
    llvm::Value *thenValue = then_exp->llvm_code(builder, module);

    // thenValue = builder->CreateLoad(thenValue->getType()->getPointerElementType(), thenValue);
    if (phiType == nullptr)
        phiType = thenValue->getType();
    else if (thenValue->getType() != phiType)
        thenValue = builder->CreateBitCast(thenValue, phiType);

    builder->CreateBr(mergeBlock);

    // Generate code for the false block
    fn->getBasicBlockList().push_back(elseBlock);
    builder->SetInsertPoint(elseBlock);

    llvm::Value *elseValue = else_exp->llvm_code(builder, module);
    if (elseValue->getType() != phiType)
        elseValue = builder->CreateBitCast(elseValue, phiType);

    builder->CreateBr(mergeBlock);

    // Merge block
    fn->getBasicBlockList().push_back(mergeBlock);
    builder->SetInsertPoint(mergeBlock);
    llvm::PHINode *phi;

    // if (llvm::isa<llvm::PHINode>(thenValue) && llvm::isa<llvm::PHINode>(elseValue))
    // {
    //     auto prevPhiNode = (llvm::PHINode *)elseValue;
    //     phi = builder->CreatePHI(thenValue->getType(), 1 + prevPhiNode->getNumIncomingValues(), "iftmp");
    //     int index = 0;
    //     phi->addIncoming(thenValue, thenBlock);
    //     std::vector<llvm::BasicBlock *> blocksToBeDeleted;
    //     std::map<std::string, bool> baz;
    //     for (auto &block : prevPhiNode->blocks())
    //     {
    //         if (!baz[(std::string)block->getSingleSuccessor()->getName()])
    //         {

    //             blocksToBeDeleted.push_back(block->getSingleSuccessor());
    //             baz[(std::string)block->getSingleSuccessor()->getName()] = true;
    //         }

    //         block->getTerminator()->setSuccessor(0, mergeBlock);

    //         phi->addIncoming(prevPhiNode->getIncomingValue(index), block);
    //         index++;
    //     }
    //     for (auto block : blocksToBeDeleted)
    //         block->removeFromParent();
    // }
    // else if (llvm::isa<llvm::PHINode>(thenValue))
    // {
    // }
    // else
    if (llvm::isa<llvm::PHINode>(elseValue))
    {

        auto prevPhiNode = (llvm::PHINode *)elseValue;
        phi = builder->CreatePHI(thenValue->getType(), 1 + prevPhiNode->getNumIncomingValues(), "iftmp");
        int index = 0;
        phi->addIncoming(thenValue, thenBlock);
        std::vector<llvm::BasicBlock *> blocksToBeDeleted;
        std::map<std::string, bool> baz;
        for (auto &block : prevPhiNode->blocks())
        {
            if (!baz[(std::string)block->getSingleSuccessor()->getName()])
            {

                blocksToBeDeleted.push_back(block->getSingleSuccessor());
                baz[(std::string)block->getSingleSuccessor()->getName()] = true;
            }

            block->getTerminator()->setSuccessor(0, mergeBlock);

            phi->addIncoming(prevPhiNode->getIncomingValue(index), block);
            index++;
        }
        for (auto block : blocksToBeDeleted)
            block->removeFromParent();
    }
    else
    {

        phi = builder->CreatePHI(phiType, 2, "iftmp");
        auto thenBlock1 = ((llvm::Instruction *)thenValue)->getParent();
        auto elseBlock1 = ((llvm::Instruction *)elseValue)->getParent();
        if (thenBlock1 == elseBlock1)
        {
            thenBlock1 = thenBlock;
            elseBlock1 = elseBlock;
        }
        phi->addIncoming(thenValue, thenBlock1);
        phi->addIncoming(elseValue, elseBlock1);
    }

    // cout << "IF done\n";

    return phi;
}

llvm::Value *loop_class::llvm_code(Builder &builder, Module &module)
{
    llvm::Function *fn = builder->GetInsertBlock()->getParent();
    llvm::BasicBlock *condBlock = llvm::BasicBlock::Create(builder->getContext(), "condBlock", fn);
    llvm::BasicBlock *startBlock = llvm::BasicBlock::Create(builder->getContext(), "startBlock");
    llvm::BasicBlock *endBlock = llvm::BasicBlock::Create(builder->getContext(), "endBlock");

    builder->CreateBr(condBlock);

    fn->getBasicBlockList().push_back(condBlock);
    builder->SetInsertPoint(condBlock);

    llvm::Value *pred_val = pred->llvm_code(builder, module);
    // if (pred_val->getType()->getPointerElementType()->isPointerTy())
    //     pred_val = builder->CreateLoad(pred_val->getType()->getPointerElementType(), pred_val);

    if (pred_val->getType() != builder->getInt1Ty())
    {
        llvm::Value *ptr_to_bool = builder->CreateStructGEP(pred_val->getType()->getPointerElementType(), pred_val, 0 + DEFAULT_OBJFIELDS);
        pred_val = builder->CreateLoad(ptr_to_bool->getType()->getPointerElementType(), ptr_to_bool);
    }

    builder->CreateCondBr(pred_val, startBlock, endBlock);

    fn->getBasicBlockList().push_back(startBlock);
    builder->SetInsertPoint(startBlock);
    llvm::Value *startValue = body->llvm_code(builder, module);
    builder->CreateBr(condBlock);

    fn->getBasicBlockList().push_back(endBlock);
    builder->SetInsertPoint(endBlock);

    auto malloc = module->getFunction("malloc");
    auto objInit = module->getFunction("Object" + (std::string)CLASSINIT_SUFFIX);
    auto mallocCall = builder->CreateCall(malloc, builder->getInt32(256));

    llvm::Value *classInstance = builder->CreateBitCast(mallocCall, objInit->getArg(0)->getType()->getPointerTo());
    builder->CreateStore(llvm::Constant::getNullValue(objInit->getArg(0)->getType()), classInstance);

    return builder->CreateLoad(classInstance->getType()->getPointerElementType(), classInstance);
}

llvm::Value *typcase_class::llvm_code(Builder &builder, Module &module)
{
    cout << "Typcase Begin\n";

    llvm::Value *pred = expr->llvm_code(builder, module);
    llvm::Function *fn = builder->GetInsertBlock()->getParent();
    // Code abort for dispatch to void
    llvm::Value *is_null = builder->CreateIsNull(pred);
    llvm::BasicBlock *isVoidBlock = llvm::BasicBlock::Create(builder->getContext(), "isVoidBlock", fn);
    llvm::BasicBlock *notVoidBlock = llvm::BasicBlock::Create(builder->getContext(), "notVoidBlock");
    builder->CreateCondBr(is_null, isVoidBlock, notVoidBlock);

    fn->getBasicBlockList().push_back(isVoidBlock);
    builder->SetInsertPoint(isVoidBlock);
    auto dump = module->getFunction("printf");
    auto exit = module->getFunction("exit");
    llvm::Value *file_name = builder->CreatePointerCast(module->getNamedGlobal("file_name"), builder->getInt8PtrTy());
    llvm::Value *_case_abort2 = builder->CreatePointerCast(module->getNamedGlobal("_case_abort2"), builder->getInt8PtrTy());
    llvm::Value *format = builder->CreateGlobalStringPtr("%s%s%s");
    llvm::Value *linenumber = builder->CreateGlobalStringPtr((std::string) ":" + std::to_string(cur_node->get_line_number()));

    builder->CreateCall(dump, {format, file_name, linenumber, _case_abort2});
    builder->CreateCall(exit, builder->getInt32(1));

    if (fn->getReturnType()->isVoidTy())
        builder->CreateRet(nullptr);
    else
        builder->CreateRet(llvm::Constant::getNullValue(fn->getReturnType()));
    fn->getBasicBlockList().push_back(notVoidBlock);
    builder->SetInsertPoint(notVoidBlock);
    // end code
    Symbol phiType = dynamic_cast<branch_class *>(cases->nth(0))->get_type();

    std::vector<int> nths;
    for (int i = cases->first(); cases->more(i); i = cases->next(i))
        nths.push_back(i);

    for (unsigned int i = 0; i < nths.size() - 1; ++i)
    {
        for (unsigned int j = i + 1; j < nths.size(); ++j)
        {
            branch_class *cas1 = dynamic_cast<branch_class *>(cases->nth(i));
            branch_class *cas2 = dynamic_cast<branch_class *>(cases->nth(j));
            int tag1 = class_table->probe(cas1->get_type())->tag;
            int tag2 = class_table->probe(cas2->get_type())->tag;
            phiType = get_lub(class_table->probe(phiType), class_table->probe(cas2->get_type()));

            if (tag1 > tag2)
            {
                int tmp;
                tmp = nths[i];
                nths[i] = nths[j];
                nths[j] = tmp;
            }
        }
    }
    llvm::Type *phiRealType = get_llvm_type(phiType, phiType);

    llvm::BasicBlock *endBlock = llvm::BasicBlock::Create(builder->getContext(), "endBlock");
    auto currentBlock = builder->GetInsertBlock();
    llvm::Value *expr_tag = builder->CreateStructGEP(pred->getType()->getPointerElementType(), pred, TAG_OFFSET);
    llvm::Value *expr_tag_i32 = builder->CreateLoad(expr_tag->getType()->getPointerElementType(), expr_tag);
    std::vector<llvm::Value *> casesValue;
    llvm::BasicBlock *currIsCaseBlock = llvm::BasicBlock::Create(builder->getContext(), "isCaseBlock");
    fn->getBasicBlockList()
        .push_back(currIsCaseBlock);
    llvm::BasicBlock *nextIsCaseBlock;
    builder->CreateBr(currIsCaseBlock);

    for (unsigned int i = 0; i < nths.size(); ++i)
    {
        llvm_tmp_table.enterscope();
        branch_class *cas = dynamic_cast<branch_class *>(cases->nth(i));
        llvm::BasicBlock *caseBlock = llvm::BasicBlock::Create(builder->getContext(), "caseBlock");
        nextIsCaseBlock = llvm::BasicBlock::Create(builder->getContext(), "isCaseBlock");
        CgenNode *nd = class_table->probe(cas->get_type());

        int min_tag = nd->tag;
        // tag najdesnijeg
        while (nd->get_children())
            for (List<CgenNode> *c = nd->get_children(); c; c = c->tl())
                nd = c->hd();
        int max_tag = nd->tag;

        builder->SetInsertPoint(currIsCaseBlock);
        builder->CreateCondBr(builder->CreateICmpEQ(expr_tag_i32, builder->getInt32(min_tag)), caseBlock, nextIsCaseBlock);
        currIsCaseBlock = nextIsCaseBlock;
        fn->getBasicBlockList()
            .push_back(currIsCaseBlock);
        fn->getBasicBlockList()
            .push_back(caseBlock);
        builder->SetInsertPoint(caseBlock);
        // llvm::Value *stackClass = builder->CreateAlloca(pred->getType(), nullptr, cas->get_name()->get_string());

        // builder->CreateStore(pred, stackClass);

        auto bar = new llvm::Value *(pred);

        llvm_tmp_table.addid(cas->get_name(), bar);
        llvm::Value *caseValue = cas->get_expr()->llvm_code(builder, module);
        if (caseValue->getType() != phiRealType)
            caseValue = builder->CreateBitCast(caseValue, phiRealType);

        casesValue.push_back(caseValue);
        builder->CreateBr(endBlock);
        llvm_tmp_table.exitscope();
    }
    builder->SetInsertPoint(currIsCaseBlock);
    // Code abort if no branches were selected
    llvm::BasicBlock *defaultBlock = llvm::BasicBlock::Create(builder->getContext(), "defaultBlock", fn);
    fn->getBasicBlockList()
        .push_back(defaultBlock);
    builder->CreateBr(defaultBlock);
    builder->SetInsertPoint(defaultBlock);
    llvm::Value *_case_abort_msg = builder->CreatePointerCast(module->getNamedGlobal("_case_abort"), builder->getInt8PtrTy());
    llvm::Function *type_name_fn = module->getFunction("Object.type_name");

    auto type_name = builder->CreateCall(type_name_fn, builder->CreateBitCast(fn->getArg(0), get_llvm_type(Object, Object)));

    auto className = builder->CreateStructGEP(type_name->getType()->getPointerElementType(), type_name, 1 + DEFAULT_OBJFIELDS);
    llvm::Value *format2 = builder->CreateGlobalStringPtr("%s%s\n");

    builder->CreateCall(dump, {format2, _case_abort_msg, builder->CreateLoad(className->getType()->getPointerElementType(), className)});
    builder->CreateCall(exit, builder->getInt32(1));

    if (fn->getReturnType()->isVoidTy())
        builder->CreateRet(nullptr);
    else
        builder->CreateRet(llvm::Constant::getNullValue(fn->getReturnType()));
    // end abort

    fn->getBasicBlockList().push_back(endBlock);
    builder->SetInsertPoint(endBlock);

    auto phi = builder->CreatePHI(phiRealType, nths.size(), "iftmp");
    for (auto caseValue : casesValue)
    {

        phi->addIncoming(caseValue, ((llvm::Instruction *)caseValue)->getParent());
    }

    cout << "Typcase Done\n";
    return phi;
}

llvm::Value *block_class::llvm_code(Builder &builder, Module &module)
{
    llvm::Value *res = nullptr;
    for (int i = body->first(); body->more(i); i = body->next(i))
        res = body->nth(i)->llvm_code(builder, module);

    return res;
}

llvm::Value *let_class::llvm_code(Builder &builder, Module &module)
{
    // cout << "Let begin\n";
    llvm::Value *init_expr;
    if (init->is_no_expr())
    {

        if (type_decl == Int)
            init_expr = get_primitive(type_decl, builder, module, builder->getInt32(0));
        else if (type_decl == Bool)
            init_expr = get_primitive(type_decl, builder, module, builder->getInt1(false));
        else if (type_decl == Str)
        {
            init_expr = get_primitive(type_decl, builder, module, builder->CreateGlobalStringPtr("", "emptyStr"));
            llvm::Value *length_field = builder->CreateStructGEP(init_expr->getType()->getPointerElementType(), init_expr, 0 + DEFAULT_OBJFIELDS);

            auto loaded_field = builder->CreateLoad(length_field->getType()->getPointerElementType(), length_field);
            builder->CreateStore(builder->getInt32(0), builder->CreateStructGEP(loaded_field->getType()->getPointerElementType(), loaded_field, 0 + DEFAULT_OBJFIELDS));
        }
        else
        {

            auto structs = module->getIdentifiedStructTypes();
            llvm::Function *malloc = module->getFunction("malloc");

            for (auto structType : structs)
            {
                if ((std::string)structType->getStructName() == type_decl->get_string())
                {
                    auto mallocCall = builder->CreateCall(malloc, builder->getInt32(256));
                    llvm::Value *classInstance = builder->CreateBitCast(mallocCall, structType->getPointerTo()->getPointerTo());
                    builder->CreateStore(llvm::Constant::getNullValue(structType->getPointerTo()), classInstance);

                    init_expr = builder->CreateLoad(classInstance->getType()->getPointerElementType(), classInstance);
                    // init_expr = classInstance;
                    break;
                }
            }
        }
    }
    else
        init_expr = init->llvm_code(builder, module);

    llvm_tmp_table.enterscope();
    llvm::Value *stackClass = builder->CreateAlloca(init_expr->getType(), nullptr, identifier->get_string());

    builder->CreateStore(init_expr, stackClass);

    // auto bar = new llvm::Value *(builder->CreateLoad(stackClass->getType()->getPointerElementType(), stackClass));
    auto bar = new llvm::Value *(stackClass);

    llvm_tmp_table.addid(identifier, bar);

    llvm::Value *result_of_body = body->llvm_code(builder, module);

    llvm_tmp_table.exitscope();
    return result_of_body;
}

llvm::Value *plus_class::llvm_code(Builder &builder, Module &module)
{
    // cout << "Plus begin\n";
    llvm::Value *L = e1->llvm_code(builder, module);

    llvm::Value *L_val = nullptr;

    // If we get literal insted of object.
    if (L->getType() == builder->getInt32Ty())
    {
        L_val = (llvm::LoadInst *)L;
    }
    // For args
    else if (L->getType()->isStructTy())
    {
        L_val = builder->CreateExtractValue(L, 0 + DEFAULT_OBJFIELDS);
    }
    // For attr
    else
    {

        auto L_pointer = builder->CreateStructGEP(L->getType()->getPointerElementType(), L, 0 + DEFAULT_OBJFIELDS);

        L_val = builder->CreateLoad(builder->getInt32Ty(), L_pointer);
    }

    llvm::Value *R = e2->llvm_code(builder, module);
    llvm::Value *R_val = nullptr;
    if (R->getType() == builder->getInt32Ty())
    {
        R_val = (llvm::LoadInst *)R;
    }
    else if (R->getType()->isStructTy())
    {
        R_val = builder->CreateExtractValue(R, 0 + DEFAULT_OBJFIELDS);
    }
    else
    {

        auto R_pointer = builder->CreateStructGEP(R->getType()->getPointerElementType(), R, 0 + DEFAULT_OBJFIELDS);

        R_val = builder->CreateLoad(builder->getInt32Ty(), R_pointer);
    }

    llvm::Value *addtmp = builder->CreateAdd(L_val, R_val, "addtmp");
    llvm::Value *intClassInstance = get_primitive(Int, builder, module, addtmp);
    // cout << "Plus done\n";
    return intClassInstance;
}

llvm::Value *sub_class::llvm_code(Builder &builder, Module &module)
{
    // cout << "Sub begin\n";
    llvm::Value *L = e1->llvm_code(builder, module);

    llvm::Value *L_val = nullptr;

    // If we get literal insted of object.
    if (L->getType() == builder->getInt32Ty())
    {
        L_val = (llvm::LoadInst *)L;
    }
    // For args
    else if (L->getType()->isStructTy())
    {
        L_val = builder->CreateExtractValue(L, 0 + DEFAULT_OBJFIELDS);
    }
    // For attr
    else
    {

        auto L_pointer = builder->CreateStructGEP(L->getType()->getPointerElementType(), L, 0 + DEFAULT_OBJFIELDS);

        L_val = builder->CreateLoad(builder->getInt32Ty(), L_pointer);
    }

    llvm::Value *R = e2->llvm_code(builder, module);
    llvm::Value *R_val = nullptr;
    if (R->getType() == builder->getInt32Ty())
    {
        R_val = (llvm::LoadInst *)R;
    }
    else if (R->getType()->isStructTy())
    {
        R_val = builder->CreateExtractValue(R, 0 + DEFAULT_OBJFIELDS);
    }
    else
    {

        auto R_pointer = builder->CreateStructGEP(R->getType()->getPointerElementType(), R, 0 + DEFAULT_OBJFIELDS);

        R_val = builder->CreateLoad(builder->getInt32Ty(), R_pointer);
    }

    llvm::Value *subtmp = builder->CreateSub(L_val, R_val, "subtmp");
    llvm::Value *intClassInstance = get_primitive(Int, builder, module, subtmp);
    // cout << "Sub done\n";
    return intClassInstance;
}

llvm::Value *mul_class::llvm_code(Builder &builder, Module &module)
{
    // cout << "Mul begin\n";
    llvm::Value *L = e1->llvm_code(builder, module);

    llvm::Value *L_val = nullptr;

    // If we get literal insted of object.
    if (L->getType() == builder->getInt32Ty())
    {
        L_val = (llvm::LoadInst *)L;
    }
    // For args
    else if (L->getType()->isStructTy())
    {
        L_val = builder->CreateExtractValue(L, 0 + DEFAULT_OBJFIELDS);
    }
    // For attr
    else
    {

        auto L_pointer = builder->CreateStructGEP(L->getType()->getPointerElementType(), L, 0 + DEFAULT_OBJFIELDS);

        L_val = builder->CreateLoad(builder->getInt32Ty(), L_pointer);
    }

    llvm::Value *R = e2->llvm_code(builder, module);
    llvm::Value *R_val = nullptr;
    if (R->getType() == builder->getInt32Ty())
    {
        R_val = (llvm::LoadInst *)R;
    }
    else if (R->getType()->isStructTy())
    {
        R_val = builder->CreateExtractValue(R, 0 + DEFAULT_OBJFIELDS);
    }
    else
    {

        auto R_pointer = builder->CreateStructGEP(R->getType()->getPointerElementType(), R, 0 + DEFAULT_OBJFIELDS);

        R_val = builder->CreateLoad(builder->getInt32Ty(), R_pointer);
    }

    llvm::Value *multmp = builder->CreateMul(L_val, R_val, "multmp");
    llvm::Value *intClassInstance = get_primitive(Int, builder, module, multmp);
    // cout << "Mul done\n";
    return intClassInstance;
}

llvm::Value *divide_class::llvm_code(Builder &builder, Module &module)
{
    // cout << "Div begin\n";
    llvm::Value *L = e1->llvm_code(builder, module);

    llvm::Value *L_val = nullptr;

    // If we get literal insted of object.
    if (L->getType() == builder->getInt32Ty())
    {
        L_val = (llvm::LoadInst *)L;
    }
    // For args
    else if (L->getType()->isStructTy())
    {
        L_val = builder->CreateExtractValue(L, 0 + DEFAULT_OBJFIELDS);
    }
    // For attr
    else
    {

        auto L_pointer = builder->CreateStructGEP(L->getType()->getPointerElementType(), L, 0 + DEFAULT_OBJFIELDS);

        L_val = builder->CreateLoad(builder->getInt32Ty(), L_pointer);
    }

    llvm::Value *R = e2->llvm_code(builder, module);
    llvm::Value *R_val = nullptr;
    if (R->getType() == builder->getInt32Ty())
    {
        R_val = (llvm::LoadInst *)R;
    }
    else if (R->getType()->isStructTy())
    {
        R_val = builder->CreateExtractValue(R, 0 + DEFAULT_OBJFIELDS);
    }
    else
    {

        auto R_pointer = builder->CreateStructGEP(R->getType()->getPointerElementType(), R, 0 + DEFAULT_OBJFIELDS);

        R_val = builder->CreateLoad(builder->getInt32Ty(), R_pointer);
    }

    llvm::Value *divtmp = builder->CreateSDiv(L_val, R_val, "divtmp");
    llvm::Value *intClassInstance = get_primitive(Int, builder, module, divtmp);
    // cout << "Div done\n";
    return intClassInstance;
}

llvm::Value *neg_class::llvm_code(Builder &builder, Module &module)
{
    llvm::Value *intClass = e1->llvm_code(builder, module);
    llvm::Value *ptrToi32 = builder->CreateStructGEP(intClass->getType()->getPointerElementType(), intClass, 0 + DEFAULT_OBJFIELDS);
    llvm::Value *i32 = builder->CreateLoad(ptrToi32->getType()->getPointerElementType(), ptrToi32);
    llvm::Value *newInt = get_primitive(Int, builder, module, builder->CreateNeg(i32, "negtmp"));

    return newInt;
}

llvm::Value *lt_class::llvm_code(Builder &builder, Module &module)
{
    // cout << "LT start\n";
    llvm::Value *L = e1->llvm_code(builder, module);
    llvm::Value *L_val;
    if (L->getType() == builder->getInt32Ty())
    {
        L_val = (llvm::LoadInst *)L;
    }
    // For args
    else if (L->getType()->isStructTy())
    {
        L_val = builder->CreateExtractValue(L, 0 + DEFAULT_OBJFIELDS);
    }
    // For attr
    else
    {

        auto L_pointer = builder->CreateStructGEP(L->getType()->getPointerElementType(), L, 0 + DEFAULT_OBJFIELDS);

        L_val = builder->CreateLoad(L_pointer->getType()->getPointerElementType(), L_pointer);
    }

    llvm::Value *R = e2->llvm_code(builder, module);
    llvm::Value *R_val;

    if (R->getType() == builder->getInt32Ty())
    {
        R_val = (llvm::LoadInst *)R;
    }
    // For args
    else if (R->getType()->isStructTy())
    {
        R_val = builder->CreateExtractValue(R, 0 + DEFAULT_OBJFIELDS);
    }
    // For attr
    else
    {

        auto R_pointer = builder->CreateStructGEP(R->getType()->getPointerElementType(), R, 0 + DEFAULT_OBJFIELDS);

        R_val = builder->CreateLoad(R_pointer->getType()->getPointerElementType(), R_pointer);
    }

    //  Integer Compare Signed Less Than
    llvm::Value *boolClassInstance = get_primitive(Bool, builder, module, builder->CreateICmpSLT(L_val, R_val, "lttmp"));

    // cout << "LT done\n";
    return boolClassInstance;
}

llvm::Value *eq_class::llvm_code(Builder &builder, Module &module)
{
    // cout << "EQ start\n";
    llvm::Value *L = e1->llvm_code(builder, module);
    llvm::Value *L_val;
    if (L->getType() == builder->getInt32Ty())
    {
        L_val = (llvm::LoadInst *)L;
    }
    // For args
    else if (L->getType()->isStructTy())
    {
        L_val = builder->CreateExtractValue(L, 0 + DEFAULT_OBJFIELDS);
    }
    // For attr
    else
    {

        auto L_pointer = builder->CreateStructGEP(L->getType()->getPointerElementType(), L, 0 + DEFAULT_OBJFIELDS);

        L_val = builder->CreateLoad(L_pointer->getType()->getPointerElementType(), L_pointer);
    }

    llvm::Value *R = e2->llvm_code(builder, module);

    llvm::Value *R_val;
    if (R->getType() == builder->getInt32Ty())
    {
        R_val = (llvm::LoadInst *)R;
    }
    // For args
    else if (R->getType()->isStructTy())
    {
        R_val = builder->CreateExtractValue(R, 0 + DEFAULT_OBJFIELDS);
    }
    // For attr
    else
    {

        auto R_pointer = builder->CreateStructGEP(R->getType()->getPointerElementType(), R, 0 + DEFAULT_OBJFIELDS);

        R_val = builder->CreateLoad(R_pointer->getType()->getPointerElementType(), R_pointer);
    }
    // Integer Compare Signed Less Than
    llvm::Value *boolClassInstance = get_primitive(Bool, builder, module, builder->CreateICmpEQ(L_val, R_val, "eqtmp"));

    // cout << "EQ done\n";
    return boolClassInstance;
}

llvm::Value *leq_class::llvm_code(Builder &builder, Module &module)
{
    // cout << "LEQ start\n";
    llvm::Value *L = e1->llvm_code(builder, module);
    llvm::Value *L_val;
    if (L->getType() == builder->getInt32Ty())
    {
        L_val = (llvm::LoadInst *)L;
    }
    // For args
    else if (L->getType()->isStructTy())
    {
        L_val = builder->CreateExtractValue(L, 0 + DEFAULT_OBJFIELDS);
    }
    // For attr
    else
    {

        auto L_pointer = builder->CreateStructGEP(L->getType()->getPointerElementType(), L, 0 + DEFAULT_OBJFIELDS);

        L_val = builder->CreateLoad(L_pointer->getType()->getPointerElementType(), L_pointer);
    }

    llvm::Value *R = e2->llvm_code(builder, module);

    llvm::Value *R_val;
    if (R->getType() == builder->getInt32Ty())
    {
        R_val = (llvm::LoadInst *)R;
    }
    // For args
    else if (R->getType()->isStructTy())
    {
        R_val = builder->CreateExtractValue(R, 0 + DEFAULT_OBJFIELDS);
    }
    // For attr
    else
    {

        auto R_pointer = builder->CreateStructGEP(R->getType()->getPointerElementType(), R, 0 + DEFAULT_OBJFIELDS);

        R_val = builder->CreateLoad(R_pointer->getType()->getPointerElementType(), R_pointer);
    }
    // Integer Compare Signed Less Than or Equal
    llvm::Value *boolClassInstance = get_primitive(Bool, builder, module, builder->CreateICmpSLE(L_val, R_val, "leqtmp"));

    // cout << "LEQ done\n";
    return boolClassInstance;
}

llvm::Value *comp_class::llvm_code(Builder &builder, Module &module)
{
    llvm::Value *boolClass = e1->llvm_code(builder, module);
    llvm::Value *ptrTobool = builder->CreateStructGEP(boolClass->getType()->getPointerElementType(), boolClass, 0 + DEFAULT_OBJFIELDS);
    llvm::Value *boolVal = builder->CreateLoad(ptrTobool->getType()->getPointerElementType(), ptrTobool);
    llvm::Value *newBool = get_primitive(Bool, builder, module, builder->CreateNot(boolVal, "nottmp"));

    return newBool;
}

llvm::Value *int_const_class::llvm_code(Builder &builder, Module &module)
{
    int real_int = atoi(inttable.lookup_string(token->get_string())->get_string());

    return get_primitive(Int, builder, module, llvm::ConstantInt::get(builder->getContext(), llvm::APInt(32, real_int)));
}

llvm::Value *string_const_class::llvm_code(Builder &builder, Module &module)
{
    StringEntry *string_literal = stringtable.lookup_string(token->get_string());

    llvm::Value *strClassInstance = get_primitive(Str, builder, module, builder->CreateGlobalStringPtr(string_literal->get_string()));

    llvm::Value *length_field = builder->CreateStructGEP(strClassInstance->getType()->getPointerElementType(), strClassInstance, 0 + DEFAULT_OBJFIELDS);

    auto loaded_field = builder->CreateLoad(length_field->getType()->getPointerElementType(), length_field);
    builder->CreateStore(builder->getInt32(string_literal->get_len()), builder->CreateStructGEP(loaded_field->getType()->getPointerElementType(), loaded_field, 0 + DEFAULT_OBJFIELDS));

    return strClassInstance;
}

llvm::Value *bool_const_class::llvm_code(Builder &builder, Module &module)
{
    // cout << "Bool begin\n";
    // cout << "val: " << val << endl;
    return get_primitive(Bool, builder, module, builder->getInt1(val));
}

llvm::Value *new__class::llvm_code(Builder &builder, Module &module)
{
    llvm::Function *classInit;
    if (type_name == SELF_TYPE)
        classInit = module->getFunction((std::string)cur_node->get_name()->get_string() + CLASSINIT_SUFFIX);
    else
        classInit = module->getFunction((std::string)type_name->get_string() + CLASSINIT_SUFFIX);

    llvm::Function *malloc = module->getFunction("malloc");
    llvm::Value *mallocCall = builder->CreateCall(malloc, builder->getInt32(256));
    llvm::Value *classInstance = builder->CreateBitCast(mallocCall, classInit->getArg(0)->getType());

    builder->CreateCall(classInit, classInstance);
    return classInstance;
}

llvm::Value *isvoid_class::llvm_code(Builder &builder, Module &module)
{
    llvm::Value *expr = e1->llvm_code(builder, module);

    llvm::Value *is_null = builder->CreateIsNull(expr);

    return get_primitive(Bool, builder, module, is_null);
}

llvm::Value *no_expr_class::llvm_code(Builder &builder, Module &module)
{
    return nullptr;
}

llvm::Value *object_class::llvm_code(Builder &builder, Module &module)
{

    auto offset = llvm_lookup_var(name);

    llvm::Function *fn = builder->GetInsertBlock()->getParent();
    cout << "Obj begin: " << name << endl;
    if (name == self)
    {
        cout << "1.Obj done: " << name << endl;

        return fn->getArg(0);
    }
    if (std::get<0>(offset))
    {
        llvm::Value *object = builder->CreateStructGEP(fn->getArg(0)->getType()->getPointerElementType(), fn->getArg(0), std::get<2>(offset), "selfPtr");
        cout << "2.Obj done: " << name << endl;

        return builder->CreateLoad(object->getType()->getPointerElementType(), object);
    }
    cout << "3.Obj done: " << name << endl;

    if (std::get<1>(offset)->getType()->getPointerElementType()->isPointerTy())
        return builder->CreateLoad(std::get<1>(offset)->getType()->getPointerElementType(), std::get<1>(offset));
    return std::get<1>(offset);
}
