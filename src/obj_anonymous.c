#include "clover.h"
#include "common.h"

void initialize_hidden_class_method_of_immediate_anonymous(sCLClass* klass)
{
    klass->mFreeFun = NULL;
    klass->mShowFun = NULL;
    klass->mMarkFun = NULL;
    klass->mCreateFun = NULL;
}

