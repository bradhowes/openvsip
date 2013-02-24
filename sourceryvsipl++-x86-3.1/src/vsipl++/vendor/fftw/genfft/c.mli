(*
 * Copyright (c) 1997-1999 Massachusetts Institute of Technology
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 *)

type stride = 
  | SVar of string
  | SConst of string
  | SInteger of int
  | SNeg of stride
val array_subscript : string -> stride -> int -> string
val varray_subscript : string -> stride -> stride -> int -> int -> string

val real_of : string -> string
val imag_of : string -> string

val realtype : string
val realtypep : string
val constrealtype : string
val constrealtypep : string
val stridetype : string

type c_decl = 
  | Decl of string * string
  | Tdecl of string                (* arbitrary text declaration *)

and c_ast =
  | Asch of Annotate.annotated_schedule
  | Return of c_ast
  | For of c_ast * c_ast * c_ast * c_ast
  | If of c_ast * c_ast
  | Block of (c_decl list) * (c_ast list)
  | Binop of string * c_ast * c_ast
  | Expr_assign of c_ast * c_ast
  | Stmt_assign of c_ast * c_ast
  | Comma of c_ast * c_ast
  | Integer of int
  | CVar of string
  | CCall of string * c_ast
  | CPlus of c_ast list
  | ITimes of c_ast * c_ast
  | CUminus of c_ast
and c_fcn = | Fcn of string * string * c_decl list * c_ast

val unparse_expr : Expr.expr -> string
val unparse_assignment : Expr.assignment -> string
val unparse_annotated : bool -> Annotate.annotated_schedule -> string
val unparse_decl : c_decl -> string
val unparse_ast : c_ast -> string
val unparse_function : c_fcn -> string

val flops_of : c_fcn -> string
val print_cost : c_fcn -> string

val ast_to_expr_list : c_ast -> Expr.expr list
val extract_constants : c_ast -> c_decl list
val ctimes : (c_ast * c_ast) -> c_ast
