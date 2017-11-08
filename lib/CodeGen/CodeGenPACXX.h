#pragma once

#include "clang/AST/RecursiveASTVisitor.h"
namespace clang{
namespace pacxx{
class KernelVisitor : public RecursiveASTVisitor<KernelVisitor> { 
  public:                              
    KernelVisitor() {}                                        
    KernelVisitor(std::vector<const FunctionDecl *> visited) : _visited(visited) {} 
    void StartFromFunctionDecl(const FunctionDecl *D) {
      if (std::find(_visited.begin(), _visited.end(), D) == std::end(_visited)) {
        _visited.push_back(D);
        TraverseFunctionDecl(const_cast<FunctionDecl*>(D)); // very very bad
      }
    }

    // PACXX FIXME: Some address space casts get still a CK_BitCast CastKind 
    // here we fix them again
    bool VisitCastExpr(CastExpr *E) {
      QualType CastTy = E->getType();
      if (CastTy->isPointerType())
        CastTy = CastTy->getPointeeType();

      if (CastTy.getAddressSpace() != LangAS::Default) {
        E->setCastKind(CastKind::CK_AddressSpaceConversion);
        return false;
      }
      return true;
   }   
                                                
  private:                                                    
    std::vector<const FunctionDecl *> _visited;         
    std::vector<const FunctionDecl *> _decl_only;                
                                                   
  };
}     
}
