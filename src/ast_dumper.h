/*
 * Copyright 2016 WebAssembly Community Group participants
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AST_DUMPER_H
#define AST_DUMPER_H

#include "wasm_ast.h"
#include "ast_visitor.h"

namespace wasm {

class AstDumper : public AstVisitor<void, void> {
 public:
  AstDumper(bool dump_types) : dump_types_(dump_types) {}

 protected:
  void VisitModule(const Module& mod) override;
  void VisitImport(const Import& imp) override;
  void VisitExport(const Export& exp) override;
  void VisitFunction(const Function& func) override;
  void VisitSegment(const Segment& seg) override;

  void VisitExpression(Expression* expr) override {
    PrintType(*expr);
    AstVisitor::VisitExpression(expr);
  }
  void VisitNop(Expression* expr) override;
  void VisitBlock(Expression* expr,
                  UniquePtrVector<Expression>* exprs) override;
  void VisitIf(Expression* expr,
               Expression* condition,
               Expression* then,
               Expression* els) override;
  void VisitCall(CallExpression* expr,
                 bool is_import,
                 Callable* callee,
                 int callee_index,
                 UniquePtrVector<Expression>* args) override;
  void VisitReturn(Expression* expr,
                   UniquePtrVector<Expression>* value) override;
  void VisitGetLocal(LocalExpression* expr, Variable* var) override;
  void VisitSetLocal(LocalExpression* expr,
                     Variable* var,
                     Expression* value) override;
  void VisitMemory(Expression* expr,
                   MemoryOperator memop,
                   MemType mem_type,
                   uint32_t mem_alignment,
                   uint64_t mem_offset,
                   bool is_signed,
                   Expression* address,
                   Expression* store_val) override;
  void VisitConst(Expression* expr, Literal* l) override;
  void VisitUnop(Expression* expr,
                 UnaryOperator unop,
                 Expression* operand) override;
  void VisitBinop(Expression* epxr,
                  BinaryOperator binop,
                  Expression* lhs,
                  Expression* rhs) override;
  void VisitCompare(Expression* expr,
                    Type compare_type,
                    CompareOperator relop,
                    Expression* lhs,
                    Expression* rhs) override;
  void VisitConversion(ConversionExpression* expr,
                       ConversionOperator cvt,
                       Expression* operand) override;

  void VisitInvoke(TestScriptExpr* expr,
                   Export* callee,
                   UniquePtrVector<Expression>* args) override;
  void VisitAssertReturn(TestScriptExpr* expr,
                         TestScriptExpr* invoke_arg,
                         UniquePtrVector<Expression>* expected) override;
  void VisitAssertReturnNaN(TestScriptExpr* expr,
                            TestScriptExpr* invoke_arg) override;
  void VisitAssertTrap(TestScriptExpr* expr,
                       TestScriptExpr* invoke_arg,
                       const std::string& text) override;

 private:
  bool dump_types_;
  void PrintType(const Expression& expr);
  friend void DumpExpr(Expression* expr, bool dump_types);
};

void DumpExpr(Expression* expr, bool dump_types);
const char* ConversionOpName(ConversionOperator cvt);
}
#endif  // AST_DUMPER_H
