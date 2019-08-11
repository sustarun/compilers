%{
	#include <stdio.h>
	extern "C" void yyerror (char *s);
	extern int yylex(void);
	extern int yylineno;
	Symbol_Table *local_symbol_table, *global_symbol_table, *formal_param_table;
	int param_number = 0;
	string curr_proc_name = "";
	string dummy_param_name = "";
	// is_main = false;
	Data_Type my_get_data_type(int type){
		Data_Type dt = void_data_type;
		if(type == 1){
			dt = int_data_type;
		}
		else if(type == 2){
			dt = double_data_type;
		}
		return dt;
	}
%}

%token INTEGER FLOAT
%token ASSIGN
%token VOID
%token NAME
%token INTEGER_NUMBER DOUBLE_NUMBER
%token IF ELSE
%token DO WHILE
%token LESS_THAN LESS_THAN_EQUAL GREATER_THAN GREATER_THAN_EQUAL EQUAL NOT_EQUAL
%token AND OR NOT
%token UMINUS
%token PRINT
%token RETURN
%union {
	int integer_value;
	double double_value;
	std::string * string_value;
	list<Ast *> * ast_list;
	Ast * ast;
	Symbol_Table * symbol_table;
	Symbol_Table_Entry * symbol_entry;
	list<Symbol_Table_Entry *> * symbol_list;
	Procedure * procedure;
}
%type<integer_value> INTEGER_NUMBER Type
%type<double_value> DOUBLE_NUMBER
%type<string_value> NAME
%type<symbol_list> Var_List
%type<ast_list> Stmt_List
%type<ast_list> Expr_List Expr_List1
%type<ast> If_block Do_While_block While_block Stmt_block
%type<ast> Assng_stmt Prnt_stmt Single_Stmt Call_stmt Retr_stmt
%type<ast> Expr Log_Expr Rel_Expr Call_expr
%type<ast> Var Const
%type<symbol_table> Var_Dec_List Var_Dec All_List Var_Dec_List1
%type<symbol_table> Param_List Param_List1 Param_Type_List
%type<procedure> Proc_Dec Proc_Def Proc_Def_List Proc_Init

%right ASSIGN
%right '?' ':'
%left OR
%left AND
%left NOT_EQUAL EQUAL
%left LESS_THAN LESS_THAN_EQUAL GREATER_THAN GREATER_THAN_EQUAL 
%left '+''-' 
%left '*' '/'
%right UMINUS
%right NOT

%nonassoc NO_ELSE
%nonassoc ELSE

%%
Prog	:	{
				global_symbol_table = new Symbol_Table();
			}
			All_List
			{
				// printf("Prog\n");
				string main_name = "main";
				if(program_object.is_procedure_exists(main_name)){
					Procedure * procedure = program_object.get_procedure_prototype(main_name);
					if(!procedure->get_return_type() == void_data_type){
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: Main should be defined and it's type should be void", yylineno);
						yyerror(err);
						exit(-1);	
					}
				}
				else{
					char err[100];
					sprintf(err, "cs316: Error: Line: %d: Main should be defined and it's type should be void", yylineno);
					yyerror(err);
					exit(-1);
				}
				// cout<<"Here111111"<<endl;
				global_symbol_table->set_table_scope(global);
				program_object.set_global_table(*global_symbol_table);
				// cout<<"Here222222"<<endl;
			}
		;

All_List	:	Proc_Def_List
				{
					// printf("All_List-1\n");
				}
			|	Proc_Dec
				All_List
				{
					// printf("All_List-2\n");
				}
			|	Var_Dec
				{
					// printf("All_List-3-1/2\n");
					global_symbol_table->append_list(*$1, yylineno);
				}
				All_List
				{
					// printf("All_List-3\n");
				}
			;

Proc_Def_List	:	Proc_Def
					{
						/*Nothing Required*/
					}
				|	Proc_Def
					Proc_Def_List
					{
						/*Nothing Required*/
					}
				;

Proc_Init	:	Type NAME '(' Param_List ')'
				{
					Data_Type return_type = my_get_data_type($1);
					std::string name = *$2;
					if(name == "main"){
						// is_main = true;
					}
					else{
						name += "_";
					}
					if(global_symbol_table->variable_in_symbol_list_check(name)){
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: Procedure name cannot be same as global variable", yylineno);
						yyerror(err);
						exit(-1);
					}
					curr_proc_name = name;
					Procedure * procedure = new Procedure(return_type, name, yylineno);
					formal_param_table = $4;
					$$ = procedure;
				}

Proc_Dec	:	Proc_Init ';'
				{
					Procedure *procedure = $1;
					string proc_name = procedure->get_proc_name();
					formal_param_table->set_table_scope(formal);
					procedure->set_formal_param_list(*formal_param_table);
					program_object.set_proc_to_map(proc_name, procedure);
					$$ = procedure;
				}
			;

Proc_Def	: 	Proc_Init '{'
				Var_Dec_List
				{
					// printf("Proc_Def-1/2\n");
					Procedure *procedure = $1;
					// cout<<"here11111"<<endl;
					string proc_name = procedure->get_proc_name();
					if(program_object.is_procedure_exists(proc_name)){
						// cout<<"here22222"<<endl;
						procedure = program_object.get_procedure_prototype(proc_name);
						if(procedure->is_proc_defined()){
							char err[100];
							sprintf(err, "cs316: Error: Line: %d: Current procedure already defined", yylineno);
							yyerror(err);
							exit(-1);
						}
						else{
							if(procedure->get_return_type() != $1->get_return_type()){
								char err[100];
								sprintf(err, "cs316: Error: Line: %d: return type in declaration and definition not matching", yylineno);
								yyerror(err);
								exit(-1);
							}
							procedure->set_proc_is_defined();
							if(formal_param_table->is_empty()){
								formal_param_table = &(procedure->get_formal_param_list());
							}
							string param1 = dummy_param_name+"1_";
							if(formal_param_table->variable_in_symbol_list_check(param1)){
								char err[100];
								sprintf(err, "cs316: Error: Line: %d: Variable name missing in parameter list", yylineno);
								yyerror(err);
								exit(-1);
							}
						}
						$1 = procedure;
					}
					else{
						program_object.set_proc_to_map(proc_name, procedure);
					}
					formal_param_table->set_table_scope(formal);
					procedure->set_formal_param_list(*formal_param_table);
					local_symbol_table = $3;
					local_symbol_table->set_table_scope(local);
					procedure->set_local_list(*local_symbol_table);
					// cout<<"here444444"<<endl;
				}
				Stmt_List
				'}'
				{
					// printf("Proc_Def\n");
					Procedure *procedure = $1;
					procedure->set_ast_list(*$5);
					$$ = procedure;
				}
			;

Param_List	:	/* No Parameters */
				{
					// printf("Param_List-1\n");
					$$ = new Symbol_Table();
				}
			|	Param_Type_List
				{
					// printf("Param_List-2\n");
					$$ = $1;
					param_number = 0;
				}
			|	Param_List1
				{
					// printf("Param_List-3\n");
					$$ = $1;
				}
			;

Param_Type_List	:	Type
					{
						// printf("Param_Type_List-1\n");
						param_number++;
						Data_Type param_type = my_get_data_type($1);
						if(param_type == void_data_type){
							char err[100];
							sprintf(err, "cs316: Error: Line: %d: Variable data type cannot be void", yylineno);
							yyerror(err);
							exit(-1);
						}
						string name = dummy_param_name + to_string(param_number) + "_";
						Symbol_Table_Entry *var = new Symbol_Table_Entry(name, param_type, yylineno);
						Symbol_Table * sym_tbl = new Symbol_Table();
						sym_tbl->push_symbol(var);
						$$ = sym_tbl;
					}
				|	Param_Type_List ',' Type
					{
						// printf("Param_Type_List-2\n");
						param_number++;
						Data_Type param_type = my_get_data_type($3);
						if(param_type == void_data_type){
							char err[100];
							sprintf(err, "cs316: Error: Line: %d: Variable data type cannot be void", yylineno);
							yyerror(err);
							exit(-1);
						}
						string name = dummy_param_name + to_string(param_number) + "_";
						Symbol_Table_Entry *var = new Symbol_Table_Entry(name, param_type, yylineno);
						Symbol_Table * sym_tbl = $1;
						sym_tbl->push_symbol(var);
						$$ = sym_tbl;
					}
				;

Param_List1	:	Type NAME
				{
					// printf("Param_List1-1\n");
					Data_Type param_type = my_get_data_type($1);
					if(param_type == void_data_type){
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: Variable data type cannot be void", yylineno);
						yyerror(err);
						exit(-1);
					}
					string name = *$2 + "_";
					Symbol_Table_Entry *var = new Symbol_Table_Entry(name, param_type, yylineno);
					Symbol_Table * sym_tbl = new Symbol_Table();
					sym_tbl->push_symbol(var);
					$$ = sym_tbl;
				}
			|	Param_List1 ',' Type NAME
				{
					// printf("Param_List1-2\n");
					Data_Type param_type = my_get_data_type($3);
					if(param_type == void_data_type){
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: Variable data type cannot be void", yylineno);
						yyerror(err);
						exit(-1);
					}
					string name = *$4 + "_";
					Symbol_Table_Entry *var = new Symbol_Table_Entry(name, param_type, yylineno);
					Symbol_Table * sym_tbl = $1;
					sym_tbl->push_symbol(var);
					$$ = sym_tbl;
				}
			;

Var_Dec_List 	:	/* empty */
					{
						// printf("Var_Dec_List-1\n");
						Symbol_Table * sym_tbl = new Symbol_Table();
						$$ = sym_tbl;
					}
				|	Var_Dec_List1
					{
						$$ = $1;
					}
				;

Var_Dec_List1 	:	Var_Dec
					{
						//printf("Var_Dec_List-1\n");
						$$ = $1;
					}
				|	Var_Dec_List1
					Var_Dec
					{
						//printf("Var_Dec_List-2\n");
						$1->append_list(*$2,yylineno);
						$$ = $1;
					}
				;

Var_Dec 	:	Type Var_List ';'
				{
					//printf("Dec-1\n");
					list<Symbol_Table_Entry*> *var_sym_list = $2;
					// var_sym_list->reverse();
					Data_Type var_type = my_get_data_type($1);
					if(var_type == void_data_type){
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: Variable data type cannot be void", yylineno);
						yyerror(err);
						exit(-1);
					}
					Symbol_Table * sym_tbl = new Symbol_Table();
					for (list<Symbol_Table_Entry*>::iterator it = var_sym_list->begin(); it !=var_sym_list->end(); ++it){
						(*it)->set_data_type(var_type);
						sym_tbl->push_symbol(*it);
					}
					$$ = sym_tbl;
				}
			;

Type	:	VOID
			{
				// printf("Type-1\n");
				$$ = 0;
			}	
		|	INTEGER
			{
				// printf("Type-2\n");
				$$ = 1;
			}
		|	FLOAT
			{
				// printf("Type-3\n");
				$$ = 2;
			}
		;

Var_List 	:	NAME
				{
					// printf("Var_List-1\n");
					// string name = *$1;
					string name = *$1 + "_";
					Symbol_Table_Entry *var = new Symbol_Table_Entry(name, void_data_type, yylineno);
					list<Symbol_Table_Entry*> *var_sym_list = new list<Symbol_Table_Entry*>();
					var_sym_list->push_back(var);
					$$ = var_sym_list;
				}
			| 	Var_List ',' NAME
				{
					// printf("Var_List-2\n");
					list<Symbol_Table_Entry*> *var_sym_list = $1;
					// string name = *$3;
					string name = *$3 + "_";
					Symbol_Table_Entry *var = new Symbol_Table_Entry(name, void_data_type, yylineno);
					var_sym_list->push_back(var);
					$$ = var_sym_list;
				}
			;

Stmt_List	: 	/*empty*/
				{
					// printf("Stmt_List-1\n");
					list<Ast*> *ast = new list<Ast*>();
					$$ = ast;
				}
			|	Stmt_List Stmt_block
				{
					// printf("Stmt_List-2\n");
					$1->push_back($2);
					$$ = $1;
				}
			;


Stmt_block	:	'{' Stmt_List '}'
				{
					Sequence_Ast *seq_ast = new Sequence_Ast(yylineno);
					list<Ast*> *stmt_list = $2;
					if(stmt_list->empty()){
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: BLock of statements cannot be empty", yylineno);
						yyerror(err);
						exit(-1);
					}
					for (list<Ast*>::iterator it = stmt_list->begin(); it !=stmt_list->end(); ++it){
						seq_ast->ast_push_back(*it);
					}
					$$ = seq_ast;
				}
			|	Single_Stmt
				{
					$$ = $1;
				}
			;

Single_Stmt 	:	If_block
					{
						$$ = $1;
					}
				|	While_block
					{
						$$ = $1;
					}
				|	Do_While_block
					{
						$$ = $1;
					}
				|	Assng_stmt
					{
						$$ = $1;	
					}
				|	Prnt_stmt
					{
						$$ = $1;
					}
				|	Call_stmt
					{
						$$ = $1;
					}
				|	Retr_stmt
					{
						$$ = $1;
					}
				;

If_block	:	IF '(' Log_Expr ')' Stmt_block %prec NO_ELSE
				{
					Selection_Statement_Ast *if_ast = new Selection_Statement_Ast($3, $5, NULL, yylineno);
					$$ = if_ast;
				}
			|	IF '(' Log_Expr ')'
				Stmt_block
				ELSE
				Stmt_block
				{
					Selection_Statement_Ast *if_else_ast = new Selection_Statement_Ast($3, $5, $7, yylineno);
					$$ = if_else_ast;
				}
			;

Do_While_block 	:	DO
					Stmt_block
					WHILE '(' Log_Expr ')' ';'
					{
						Iteration_Statement_Ast *do_whl_ast = new Iteration_Statement_Ast($5, $2, yylineno, true);
						$$ = do_whl_ast;
					}
				;

While_block 	:	WHILE '(' Log_Expr ')'
					Stmt_block
					{
						Iteration_Statement_Ast *whl_ast = new Iteration_Statement_Ast($3, $5, yylineno, false);
						$$ = whl_ast;
					}
				;


Assng_stmt 	: 	Var ASSIGN Expr ';'
				{
					// printf("Assng_stmt\n");
					Assignment_Ast *assign_ast = new Assignment_Ast($1, $3, yylineno);
					assign_ast->check_ast();
					$$ = assign_ast;
				}
			|	Var ASSIGN Call_expr ';'
				{
					// printf("Assng_stmt\n");
					Call_Ast *call_ast = (Call_Ast*)$3;
					Register_Descriptor *ret_reg = new Register_Descriptor();
					call_ast->set_register(ret_reg);
					Assignment_Ast *assign_ast = new Assignment_Ast($1, call_ast, yylineno);
					assign_ast->check_ast();
					$$ = assign_ast;
				}
			;

Prnt_stmt	:	PRINT Var ';'
				{
					Print_Ast *prnt_ast = new Print_Ast($2, yylineno);
					$$ = prnt_ast;
				}
			;

Call_stmt	:	Call_expr ';'
				{
					$$ = $1;
				}


Retr_stmt	:	RETURN Expr ';'
				{
					Procedure *procedure = program_object.get_procedure_prototype(curr_proc_name);
					if(procedure->get_return_type() == $2->get_data_type()){
						Return_Ast *retr_ast = new Return_Ast($2,curr_proc_name, yylineno);
						$$ = retr_ast;
					}
					else{
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: Return type not matching", yylineno);
						yyerror(err);
						exit(-1);
					}
				}
			|	RETURN ';'
				{
					Procedure *procedure = program_object.get_procedure_prototype(curr_proc_name);
					if(procedure->get_return_type() == void_data_type){
						Ast *ast = NULL;
						Return_Ast *retr_ast = new Return_Ast(ast, curr_proc_name, yylineno);
						$$ = retr_ast;
					}
					else{
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: Return type not matching", yylineno);
						yyerror(err);
						exit(-1);
					}
				}

Log_Expr	:	Log_Expr OR Log_Expr
				{
					Logical_Expr_Ast *and_ast = new Logical_Expr_Ast($1, _logical_or, $3, yylineno);
					and_ast->check_ast();
					$$ = and_ast;
				}
			|	Log_Expr AND Log_Expr
				{
					Logical_Expr_Ast *or_ast = new Logical_Expr_Ast($1, _logical_and, $3, yylineno);
					or_ast->check_ast();
					$$ = or_ast;
				}
			|	NOT Log_Expr
				{
					Logical_Expr_Ast *not_ast = new Logical_Expr_Ast(NULL, _logical_not, $2, yylineno);
					not_ast->check_ast();
					$$ = not_ast;
				}
			|	'(' Log_Expr ')'
				{
					$$ = $2;
				}
			|	Rel_Expr
				{
					// printf("Log_Expr_b-2\n");
					$$ = $1;
				}
			;

Rel_Expr	:	Expr LESS_THAN Expr
				{
					// printf("Rel_Expr-1\n");
					Relational_Expr_Ast *lt_ast = new Relational_Expr_Ast($1, less_than, $3, yylineno);
					lt_ast->check_ast();
					$$ = lt_ast;
				}
			|	Expr LESS_THAN_EQUAL Expr
				{
					Relational_Expr_Ast *lte_ast = new Relational_Expr_Ast($1, less_equalto, $3, yylineno);
					lte_ast->check_ast();
					$$ = lte_ast;
				}
			|	Expr GREATER_THAN Expr
				{
					Relational_Expr_Ast *gt_ast = new Relational_Expr_Ast($1, greater_than, $3, yylineno);
					gt_ast->check_ast();
					$$ = gt_ast;
				}
			|	Expr GREATER_THAN_EQUAL Expr
				{
					Relational_Expr_Ast *gte_ast = new Relational_Expr_Ast($1, greater_equalto, $3, yylineno);
					gte_ast->check_ast();
					$$ = gte_ast;
				}
			|	Expr EQUAL Expr
				{
					Relational_Expr_Ast *e_ast = new Relational_Expr_Ast($1, equalto, $3, yylineno);
					e_ast->check_ast();
					$$ = e_ast;	
				}
			|	Expr NOT_EQUAL Expr
				{
					Relational_Expr_Ast *ne_ast = new Relational_Expr_Ast($1, not_equalto, $3, yylineno);
					ne_ast->check_ast();
					$$ = ne_ast;
				}
			;

Call_expr	:	NAME '(' Expr_List ')'
				{
					string proc_name = *$1 + "_";
					if(program_object.is_procedure_exists(proc_name)){
						Procedure *procedure = program_object.get_procedure_prototype(proc_name);
						procedure->set_proc_is_called();
						Symbol_Table *formal_param_list = &(procedure->get_formal_param_list());
						Call_Ast *call_ast = new Call_Ast(proc_name, yylineno);
						call_ast->set_actual_param_list(*$3);
						call_ast->check_actual_formal_param(*formal_param_list);
						$$ = call_ast;
					}
					else{
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: Called procedure does not exist", yylineno);
						yyerror(err);
						exit(-1);
					}
				}
			;

Expr_List	:	/*Empty*/
				{
					list<Ast*> *list_ast = new list<Ast*>();
					$$ = list_ast;
				}
			|	Expr_List1
				{
					$$ = $1;
				}

Expr_List1	:	Expr
				{
					list<Ast*> *list_ast = new list<Ast*>();
					list_ast->push_back($1);
					$$ = list_ast;
				}
			|	Expr_List1 ',' Expr
				{
					$1->push_back($3);
					$$ = $1;
				}


Expr 	: 	Log_Expr '?' Expr ':' Expr
			{
				Conditional_Expression_Ast *cond_ast = new Conditional_Expression_Ast($1, $3, $5, yylineno);
				cond_ast->check_ast();
				$$ = cond_ast;
			}
		|	Expr '+' Expr
			{
				// printf("Expr-1\n");
				Plus_Ast *plus_ast = new Plus_Ast($1, $3, yylineno);
				plus_ast->check_ast();
				$$ = plus_ast;
			}
		| 	Expr '-' Expr
			{
				// printf("Expr-2\n");
				Minus_Ast *minus_ast = new Minus_Ast($1, $3, yylineno);
				minus_ast->check_ast();
				$$ = minus_ast;
			}
		| 	Expr '*' Expr
			{
				// printf("Expr_a-1\n");
				Mult_Ast *mult_ast = new Mult_Ast($1, $3, yylineno);
				mult_ast->check_ast();
				$$ = mult_ast;
			}
		| 	Expr '/' Expr
			{
				// printf("Expr_a-2\n");
				Divide_Ast *divide_ast = new Divide_Ast($1, $3, yylineno);
				divide_ast->check_ast();
				$$ = divide_ast;
			}
		|	'-' Expr %prec UMINUS
			{
				// printf("Expr_b-1\n");
				UMinus_Ast *uminus_ast = new UMinus_Ast($2, NULL, yylineno);
				uminus_ast->check_ast();
				$$ = uminus_ast;
			}
		| 	'(' Expr ')'
			{
				// printf("Expr_d-1\n");
				$$ = $2;
			}
		|	Var
			{
				// printf("Expr_d-2\n");
				$$ = $1;
			}
		| 	Const
			{
				// printf("Expr_d-3\n");
				$$ = $1;
			}
		;

Var 	: 	NAME
			{
				// printf("Var\n");
				// string var = *$1;
				string var = *$1 + "_";
				Symbol_Table_Entry *var_sym_entry;
				int err =0;
				// cout<<"here11111"<<endl;
				if(local_symbol_table->variable_in_symbol_list_check(var)){
					// cout<<"here22222"<<endl;
					var_sym_entry = &(local_symbol_table->get_symbol_table_entry(var));
				}
				else if(formal_param_table->variable_in_symbol_list_check(var)){
					// cout<<"here33333"<<endl;
					var_sym_entry = &(formal_param_table->get_symbol_table_entry(var));
				}
				else if(global_symbol_table->variable_in_symbol_list_check(var)){
					// cout<<"here44444"<<endl;
					var_sym_entry = &(global_symbol_table->get_symbol_table_entry(var));
				}
				else{
					// cout<<"here55555"<<endl;
					err = 1;
				}
				if(err){
					char err[100];
					sprintf(err, "cs316: Error: Line: %d: Variable has not been declared", yylineno);
					yyerror(err);
					exit(-1);
				}
				else{
					Name_Ast *name_ast = new Name_Ast(var, *var_sym_entry, yylineno);
					$$ = name_ast;
				}
				// printf("exit Var\n");
			}
		;

Const 	: 	INTEGER_NUMBER
			{
				// printf("Const-1\n");
				Number_Ast<int> *int_ast = new Number_Ast<int>($1, int_data_type, yylineno);
				$$ = int_ast;
			}
		| 	DOUBLE_NUMBER
			{
				// printf("Const-2\n");
				Number_Ast<double> *float_ast = new Number_Ast<double>($1, double_data_type, yylineno);
				$$ = float_ast;
			}
		;
%%
