
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/Support/raw_ostream.h"

#include <iostream>

using namespace llvm;

namespace {
  class FunctionInfo : public FunctionPass {
  public:
    static char ID;
    FunctionInfo() : FunctionPass(ID) { }
    ~FunctionInfo() { }

    // We don't modify the program, so we preserve all analyses
    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
    }

    // Do some initialization
    bool doInitialization(Module &M) override {
      errs() << "CSE521 Function Information Pass\n"; // TODO: remove this.
      // outs() << "Name,\tArgs,\tCalls,\tBlocks,\tInsns\n";

      return false;
    }

    // Print output for each function
    bool runOnFunction(Function &F) override {
      // outs() << "name" << ",\t" << "args" << ",\t" << "calls" << ",\t" << "bbs" << ",\t" << "insts" << "\n";
            // outs() << "name" << ",\t" << "args" << ",\t" << "calls" << ",\t" << "bbs" << ",\t" << "insts" << "\n";
      int arg_count = 0, bb_count = 0, i_count = 0;

      for (auto i = F.args().begin(); i < F.args().end(); i++)
          arg_count++;
      
      for (auto& B : F)
         {
            bb_count++;
            for (auto& I : B)
              {
                i_count++;
              }    
         }
      errs() << "\nFunction name is " << F.getName();
      errs() << "\nThe number of arguments in this function are " << arg_count;
      errs() << "\nThe number of basic blocks in this function are " << bb_count;
      errs() << "\nThe number of instructions in this function are " << i_count;

      return false;
    }
  };
}

// LLVM uses the address of this static member to identify the pass, so the
// initialization value is unimportant.
char FunctionInfo::ID = 0;
static RegisterPass<FunctionInfo> X("function-info", "CSE521: Function Information", false, false);
/*
int main(){
	return 0;
}
*/
