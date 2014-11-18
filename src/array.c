#include "clover.h"
#include "common.h"

static void show_array_object_to_stdout(CLObject obj)
{
    int j;

    printf(" item id %u ", CLARRAY(obj)->mItems);
    printf(" (size %d) (len %d) \n", CLARRAY(obj)->mSize, CLARRAY(obj)->mLen);

    for(j=0; j<CLARRAY(obj)->mLen; j++) {
        printf(" item##%d %d\n", j, CLARRAY_ITEMS(obj, j).mObjectValue.mValue);
    }
}

static unsigned int items_object_size(int mvalue_num)
{
    unsigned int size;

    size = sizeof(sCLArrayItems) - sizeof(MVALUE) * DUMMY_ARRAY_SIZE + sizeof(MVALUE) * mvalue_num;

    /// align to 4 byte boundry
    size = (size + 3) & ~3;

    return size;
}

static CLObject alloc_array_items(int mvalue_num)
{
    int item_heap_size;

    item_heap_size = items_object_size(mvalue_num);

    return alloc_heap_mem(item_heap_size, 0);
}

static unsigned int object_size()
{
    unsigned int size;

    size = sizeof(sCLArray);

    /// align to 4 byte boundry
    size = (size + 3) & ~3;

    return size;
}

static CLObject alloc_array_object(CLObject type_object, int mvalue_num, sVMInfo* info)
{
    int heap_size;
    CLObject obj;
    int item_heap_size;
    volatile CLObject items;

    heap_size = object_size();
    obj = alloc_heap_mem(heap_size, type_object);
    push_object(obj, info);

    CLARRAY(obj)->mSize = mvalue_num;
    items = alloc_array_items(mvalue_num);
    CLARRAY(obj)->mItems = items;

    pop_object(info);

    return obj;
}

CLObject create_array_object(CLObject type_object, MVALUE elements[], int num_elements, sVMInfo* info)
{
    CLObject obj;
    MVALUE* data;

    const int mvalue_num = (num_elements + 1) * 2;

    obj = alloc_array_object(type_object, mvalue_num, info);

    CLARRAY(obj)->mLen = num_elements;

    if(num_elements > 0) {
        int j;

        data = CLARRAYITEMS(CLARRAY(obj)->mItems)->mData;
        for(j=0; j<num_elements; j++) {
            data[j] = elements[j];
        }
    }

    return obj;
}

static void mark_array_object(CLObject object, unsigned char* mark_flg)
{
    int i;

    CLObject object2 = CLARRAY(object)->mItems;
    mark_object(object2, mark_flg);

    for(i=0; i<CLARRAY(object)->mLen; i++) {
        CLObject object3 = CLARRAY_ITEMS(object, i).mObjectValue.mValue;

        mark_object(object3, mark_flg);
    }
}

static void show_array_object(sVMInfo* info, CLObject obj)
{
    int j;

    VMLOG(info, " item id %lu ", CLARRAY(obj)->mItems);
    VMLOG(info, " (size %d) (len %d) \n", CLARRAY(obj)->mSize, CLARRAY(obj)->mLen);

    for(j=0; j<CLARRAY(obj)->mLen; j++) {
        VMLOG(info, " item##%d %d\n", j, CLARRAY_ITEMS(obj, j).mObjectValue);
    }
}

static void add_to_array(CLObject self, MVALUE item, sVMInfo* info)
{
    CLObject items;

    if(CLARRAY(self)->mLen >= CLARRAY(self)->mSize) {
        CLObject old_items;
        int new_mvalue_num;
        volatile CLObject items;

        push_object(self, info);
        push_object(CLARRAY(self)->mItems, info);
        
        new_mvalue_num = (CLARRAY(self)->mSize+1) * 2;
        old_items = CLARRAY(self)->mItems;

        items = alloc_array_items(new_mvalue_num);

        memcpy(CLARRAYITEMS(items)->mData, CLARRAYITEMS(old_items)->mData, sizeof(MVALUE)*CLARRAY(self)->mLen);

        CLARRAY(self)->mItems = items;
        CLARRAY(self)->mSize = new_mvalue_num;


        pop_object(info);
        pop_object(info);
    }

    items = CLARRAY(self)->mItems;

    CLARRAYITEMS(items)->mData[CLARRAY(self)->mLen] = item;
    CLARRAY(self)->mLen++;
}

/// no check index range
static MVALUE get_item_from_array(CLObject self, int index)
{
    return CLARRAYITEMS(CLARRAY(self)->mItems)->mData[index];
}

void initialize_hidden_class_method_of_array(sCLClass* klass)
{
    klass->mFreeFun = NULL;
    klass->mShowFun = show_array_object;
    klass->mMarkFun = mark_array_object;
    klass->mCreateFun = NULL;
}

BOOL Array_Array(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info)
{
    CLObject self;

    self = lvar->mObjectValue.mValue;

    (*stack_ptr)->mObjectValue.mValue = self;
    (*stack_ptr)++;

    return TRUE;
}

BOOL Array_add(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info)
{
    CLObject self;
    MVALUE* item;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;
    item = lvar+1;

    add_to_array(self, *item, info);

    vm_mutex_unlock();

    return TRUE;
}

BOOL Array_items(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info)
{
    CLObject self;
    int index;
    CLObject ovalue1;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;
    ovalue1 = (lvar+1)->mObjectValue.mValue;
    index = CLINT(ovalue1)->mValue;

    if(index < 0) { index += CLARRAY(self)->mLen; }

    if(index < 0 || index >= CLARRAY(self)->mLen) {
        entry_exception_object(info, gExRangeClass, "range exception");
        vm_mutex_unlock();
        return FALSE;
    }

    (*stack_ptr)->mObjectValue.mValue = get_item_from_array(self, index).mObjectValue.mValue;
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}

BOOL Array_length(MVALUE** stack_ptr, MVALUE* lvar, sVMInfo* info)
{
    CLObject self;

    vm_mutex_lock();

    self = lvar->mObjectValue.mValue;

    (*stack_ptr)->mObjectValue.mValue = create_int_object(CLARRAY(self)->mLen);
    (*stack_ptr)++;

    vm_mutex_unlock();

    return TRUE;
}

