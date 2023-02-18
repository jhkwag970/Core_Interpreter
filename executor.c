#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "core.h"
#include "tree.h"
#include "executor.h"
#include "parser.h"
#include "memory.h"

#define TAB 4

void executeProcedure();
void executeDeclSeq(struct nodeDeclSeq *ds2);
void executeStmtSeq(struct nodeStmtSeq *ss2);
void executeDecl(struct nodeDecl *d2);
void executeDeclInteger(struct nodeDeclInteger *di2);
void executeDeclRecord(struct nodeDeclRecord *dr2);
void executeStmt(struct nodeStmt *s2);
void executeAssign(struct nodeAssign *ass2);
void executeIf(struct nodeIf *i2);
void executeLoop(struct nodeLoop *lp2);
void executeOut(struct nodeOut *out2);
void executeIndex(struct nodeIndex *idx2);
void executeExpr(struct nodeExpr *exp2);
void executeTerm(struct nodeTerm *tm2);
void executeFactor(struct nodeFactor *fac2);
void executeCond(struct nodeCond *c2);
void executeCmpr(struct nodeCmpr *cmp2);

extern struct nodeProcedure *p;
static int indentSize;

/*
*
* Helper functions
*
*/

static void indents(int indent) {
	for (int i=0; i<indent; i++) {
		printf("  ");
	}
}

/*
*
* Print functions go here
*
*/

void executeTree(){
	memory_init();
	printProcedure();
	free(p);
}

void executeProcedure(){

	executeDeclSeq(p->ds);

	executeStmtSeq(p->ss);
}


void executeDeclSeq(struct nodeDeclSeq *ds2){

	executeDecl(ds2->d);
	if(ds2->ds != NULL){
		executeDeclSeq(ds2->ds);
	}
}

void executeDecl(struct nodeDecl *d2){
	if(d2->di != NULL){
		executeDeclInteger(d2->di);
	}
	if(d2->dr != NULL){
		executeDeclRecord(d2->dr);
	}
}

void executeDeclInteger(struct nodeDeclInteger *di2){
	//printf("integer %s;\n",di2->id);
	declare(di2->id, INTEGER);
}

void executeDeclRecord(struct nodeDeclRecord *dr2){
	//printf("record %s;\n",dr2->id);
	declare(dr2->id, RECORD);
}

void executeStmtSeq(struct nodeStmtSeq *ss2){
	printStmt(ss2->s);

	if(ss2->ss != NULL){
		printStmtSeq(ss2->ss);
		free(ss2->ss);
	}

	free(ss2->s);
}

void executeStmt(struct nodeStmt *s2){
	if(s2->ass != NULL){
		printAssign(s2->ass);
		free(s2->ass);
	}
	if(s2->i != NULL){
		printIf(s2->i);
		free(s2->i);
	}
	if(s2->lp != NULL){
		printLoop(s2->lp);
		free(s2->lp);
	}
	if(s2->out != NULL){
		printOut(s2->out);
		free(s2->out);
	}
}

void executeAssign(struct nodeAssign *ass2){
	indents(indentSize);
	printf("%s", ass2->id);
	if(ass2->idx != NULL){
		printIndex(ass2->idx);
		printf(":=");
		printExpr(ass2->exp);

		free(ass2->idx);
		free(ass2->exp);
	}else if(ass2->exp != NULL){
		printf(":=new record[");
		printExpr(ass2->exp);
		printf("]");

		free(ass2->exp);
	}else if(ass2->id2 != NULL){
		printf(":=record %s", ass2->id2);
		free(ass2->id2);
	}	
	printf(";\n");
	free(ass2->id);

}

void executeIndex(struct nodeIndex *idx2){
	if(idx2->exp != NULL){
		printf("[");
		printExpr(idx2->exp);
		printf("]");
		free(idx2->exp);
	}
}

void executeIf(struct nodeIf *i2){
	indents(indentSize);
	printf("if ");
	printCond(i2->c);
	printf(" then\n");
	indentSize+=TAB;
	printStmtSeq(i2->ss);

	if(i2->ss2 != NULL){
		indentSize-=TAB;
		indents(indentSize);
		printf("else\n");
		indentSize+=TAB;
		printStmtSeq(i2->ss2);
		free(i2->ss2);
	}
	indentSize-=TAB;
	indents(indentSize);
	printf("end\n");

	free(i2->c);
	free(i2->ss);
}

void executeCond(struct nodeCond *c2){
	if(c2->cmp !=NULL){
		printCmpr(c2->cmp);
		if(c2->c != NULL){
			if(!strcmp(c2->sign, "or")){
				printf("or ");
			}else if(!strcmp(c2->sign, "and")){
				printf("and ");
			}
			printCond(c2->c);

			free(c2->sign);
			free(c2->c);
		}
		free(c2->cmp);
	}else{
		printf("not ");
		printCond(c2->c);
		free(c2->c);
	}
}

void executeCmpr(struct nodeCmpr *cmp2){
	printExpr(cmp2->exp);
	if(!strcmp(cmp2->sign, "=")){
		printf("=");
	}else if(!strcmp(cmp2->sign, "<")){
		printf("<");
	}
	printExpr(cmp2->exp2);

	free(cmp2->exp);
	free(cmp2->sign);
	free(cmp2->exp2);
}

void executeLoop(struct nodeLoop *lp2){
	indents(indentSize);
	printf("while ");
	printCond(lp2->c);
	printf(" do\n");
	indentSize+=TAB;
	printStmtSeq(lp2->ss);
	indentSize-=TAB;
	indents(indentSize);
	printf("end\n");

	free(lp2->c);
	free(lp2->ss);
}

void executeOut(struct nodeOut *out2){
	indents(indentSize);
	printf("out(");
	printExpr(out2->exp);
	printf(");\n");
	free(out2->exp);
}

void executeExpr(struct nodeExpr *exp2){
	printTerm(exp2->tm);

	if(exp2->math != NULL){
		if(!strcmp(exp2->math, "+")){
			printf("+");
		}else if(!strcmp(exp2->math, "-")){
			printf("-");
		}
		printExpr(exp2->exp);
		free(exp2->exp);
	}
	free(exp2->tm);
	

}

void executeTerm(struct nodeTerm *tm2){
	printFactor(tm2->fac);
	
	if(tm2->math != NULL){
		if(!strcmp(tm2->math, "*")){
			printf("*");
		}else if(!strcmp(tm2->math, "/")){
			printf("/");
		}
		printTerm(tm2->tm);
		free(tm2->tm);
	}
	free(tm2->fac);
	
}

void executeFactor(struct nodeFactor *fac2){
	if(fac2->id != NULL){
		printf("%s", fac2->id);
		if(fac2->exp != NULL){
			printf("[");
			printExpr(fac2->exp);
			printf("]");
			free(fac2->exp);
		}
		free(fac2->id);
	}else if(fac2->cnt != -1){
		printf("%d", fac2->cnt);
	}else if(fac2->exp != NULL){
		printf("(");
		printExpr(fac2->exp);
		printf(")");
		free(fac2->exp);
	}else{
		printf("in()");
	}
}
