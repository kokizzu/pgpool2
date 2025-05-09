/*-------------------------------------------------------------------------
 *
 * makefuncs.h
 *	  prototypes for the creator functions of various nodes
 *
 *
 * Portions Copyright (c) 2003-2024, PgPool Global Development Group
 * Portions Copyright (c) 1996-2024, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/nodes/makefuncs.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef MAKEFUNC_H
#define MAKEFUNC_H

#include "parsenodes.h"


extern A_Expr *makeA_Expr(A_Expr_Kind kind, List *name,
						  Node *lexpr, Node *rexpr, int location);

extern A_Expr *makeSimpleA_Expr(A_Expr_Kind kind, char *name,
								Node *lexpr, Node *rexpr, int location);

extern Var *makeVar(int varno,
					AttrNumber varattno,
					Oid vartype,
					int32 vartypmod,
					Oid varcollid,
					Index varlevelsup);

extern Var *makeVarFromTargetEntry(int varno,
								   TargetEntry *tle);

extern Var *makeWholeRowVar(RangeTblEntry *rte,
							int varno,
							Index varlevelsup,
							bool allowScalar);

extern TargetEntry *makeTargetEntry(Expr *expr,
									AttrNumber resno,
									char *resname,
									bool resjunk);

extern TargetEntry *flatCopyTargetEntry(TargetEntry *src_tle);

extern FromExpr *makeFromExpr(List *fromlist, Node *quals);

extern Const *makeConst(Oid consttype,
						int32 consttypmod,
						Oid constcollid,
						int constlen,
						Datum constvalue,
						bool constisnull,
						bool constbyval);

extern Const *makeNullConst(Oid consttype, int32 consttypmod, Oid constcollid);

extern Node *makeBoolConst(bool value, bool isnull);

extern Expr *makeBoolExpr(BoolExprType boolop, List *args, int location);

extern Alias *makeAlias(const char *aliasname, List *colnames);

extern RelabelType *makeRelabelType(Expr *arg, Oid rtype, int32 rtypmod,
									Oid rcollid, CoercionForm rformat);

extern RangeVar *makeRangeVar(char *schemaname, char *relname, int location);

extern TypeName *makeTypeName(char *typnam);
extern TypeName *makeTypeNameFromNameList(List *names);
extern TypeName *makeTypeNameFromOid(Oid typeOid, int32 typmod);

extern ColumnDef *makeColumnDef(const char *colname,
								Oid typeOid, int32 typmod, Oid collOid);

extern FuncExpr *makeFuncExpr(Oid funcid, Oid rettype, List *args,
							  Oid funccollid, Oid inputcollid, CoercionForm fformat);

extern FuncCall *makeFuncCall(List *name, List *args,
							  CoercionForm funcformat, int location);

extern Node *makeStringConst(char *str, int location);
extern DefElem *makeDefElem(char *name, Node *arg, int location);
extern DefElem *makeDefElemExtended(char *nameSpace, char *name, Node *arg,
									DefElemAction defaction, int location);

extern GroupingSet *makeGroupingSet(GroupingSetKind kind, List *content, int location);

extern VacuumRelation *makeVacuumRelation(RangeVar *relation, Oid oid, List *va_cols);

extern JsonFormat *makeJsonFormat(JsonFormatType type, JsonEncoding encoding,
								  int location);
extern JsonValueExpr *makeJsonValueExpr(Expr *raw_expr, Expr *formatted_expr,
										JsonFormat *format);
extern Node *makeJsonKeyValue(Node *key, Node *value);
extern Node *makeJsonIsPredicate(Node *expr, JsonFormat *format,
								 JsonValueType item_type, bool unique_keys,
								 int location);
extern JsonBehavior *makeJsonBehavior(JsonBehaviorType btype, Node *expr,
									  int location);
extern JsonTablePath *makeJsonTablePath(Const *pathvalue, char *pathname);
extern JsonTablePathSpec *makeJsonTablePathSpec(char *string, char *name,
												int string_location,
												int name_location);

#endif							/* MAKEFUNC_H */
