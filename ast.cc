#include <string.h>
#include <stdlib.h>
extern "C" void yyerror (char *s);

template class Number_Ast<double>;
template class Number_Ast<int>;

int Ast::labelCounter;


void lhs_rhs_print1(Ast *lhs, Ast *rhs, ostream & file_buffer){
	char lhs_start_str[] = "            LHS (";
	int str_size = strlen(lhs_start_str);
	file_buffer.write(lhs_start_str,str_size);

	lhs->print(file_buffer);

	char lhs_end_str[] = ")\n";
	str_size = strlen(lhs_end_str);
	file_buffer.write(lhs_end_str,str_size);

	char rhs_start_str[] = "            RHS (";
	str_size = strlen(rhs_start_str);
	file_buffer.write(rhs_start_str,str_size);
	
	rhs->print(file_buffer);
	
	char rhs_end_str[] = ")";
	str_size = strlen(rhs_end_str);
	file_buffer.write(rhs_end_str,str_size);
}

void lhs_rhs_print2(Ast *lhs, Ast *rhs, ostream & file_buffer){
	char lhs_start_str[] = "               LHS (";
	int str_size = strlen(lhs_start_str);
	file_buffer.write(lhs_start_str,str_size);

	lhs->print(file_buffer);

	char lhs_end_str[] = ")\n";
	str_size = strlen(lhs_end_str);
	file_buffer.write(lhs_end_str,str_size);

	char rhs_start_str[] = "               RHS (";
	str_size = strlen(rhs_start_str);
	file_buffer.write(rhs_start_str,str_size);
	
	rhs->print(file_buffer);
	
	char rhs_end_str[] = ")";
	str_size = strlen(rhs_end_str);
	file_buffer.write(rhs_end_str,str_size);
}



Ast::Ast(){}
Ast::~Ast(){}
Data_Type Ast::get_data_type(){
	return this->node_data_type;
}
void Ast::set_data_type(Data_Type dt){
	this->node_data_type = dt;
}
bool Ast::is_value_zero(){
	return false;
}
bool Ast::check_ast(){
	return false;
}
Symbol_Table_Entry & Ast::get_symbol_entry(){}


Assignment_Ast::Assignment_Ast(Ast * temp_lhs, Ast * temp_rhs, int line){
	this->lhs = temp_lhs;
	this->rhs = temp_rhs;
	this->lineno = line;
	this->ast_num_child = binary_arity;
}
Assignment_Ast::~Assignment_Ast(){}
bool Assignment_Ast::check_ast(){
	if((this->rhs) == NULL){
		this->node_data_type = (this->lhs)->get_data_type();
		return true;
	}
	else if((this->lhs)->get_data_type() == (this->rhs)->get_data_type()){
		this->node_data_type = (this->lhs)->get_data_type();
		return true;
	}
	else{
		char err[100];
		sprintf(err, "cs316: Error: Line: %d: Assignment statement data type not compatible", this->lineno); 
		yyerror(err);
		exit(-1);
		// return false;
	}
}
void Assignment_Ast::print(ostream & file_buffer){
	char assgn_str[] = "\n         Asgn:\n";
	int str_size = strlen(assgn_str);
	file_buffer.write(assgn_str,str_size);

	lhs_rhs_print1(this->lhs, this->rhs, file_buffer);
}


Name_Ast::Name_Ast(string & name, Symbol_Table_Entry & var_entry, int line){
	this->variable_symbol_entry = &var_entry;
	this->lineno = line;
	this->ast_num_child = zero_arity;
	this->node_data_type = var_entry.get_data_type();
}
Name_Ast::~Name_Ast(){}
Data_Type Name_Ast::get_data_type(){
	return this->node_data_type;
}
void Name_Ast::set_data_type(Data_Type dt){
	this->node_data_type = dt;
}
Symbol_Table_Entry & Name_Ast::get_symbol_entry(){
	return *(this->variable_symbol_entry);
}
void Name_Ast::print(ostream & file_buffer){
	char name_str[] = "Name : ";
	int str_size = strlen(name_str);
	file_buffer.write(name_str,str_size);

	string str = (this->variable_symbol_entry)->get_variable_name();
	char var_str[100];
	strcpy(var_str, str.c_str());
	str_size = strlen(var_str);
	file_buffer.write(var_str,str_size);
}


template <class T>
Number_Ast<T>::Number_Ast(T number, Data_Type constant_data_type, int line){
	this->constant = number;
	this->node_data_type = constant_data_type;
	this->lineno = line;
	this->ast_num_child = zero_arity;
}
template <class T>
Number_Ast<T>::~Number_Ast(){}
template <class T>
Data_Type Number_Ast<T>::get_data_type(){
	return this->node_data_type;
}
template <class T>
void Number_Ast<T>::set_data_type(Data_Type dt){
	this->node_data_type = dt;
}
template <class T>
bool Number_Ast<T>::is_value_zero(){
	if(this->constant == 0){
		return true;
	}
	else{
		return false;
	}
}
template <class T>
void Number_Ast<T>::print(ostream & file_buffer){
	char num_str[] = "Num : ";
	int str_size = strlen(num_str);
	file_buffer.write(num_str,str_size);
	file_buffer<<(this->constant);
}


Data_Type Arithmetic_Expr_Ast::get_data_type(){
	return this->node_data_type;
}
void Arithmetic_Expr_Ast::set_data_type(Data_Type dt){
	this->node_data_type = dt;
}
bool Arithmetic_Expr_Ast::check_ast(){
	if((this->rhs) == NULL){
		this->node_data_type = (this->lhs)->get_data_type();
		return true;
	}
	else if((this->lhs)->get_data_type() == (this->rhs)->get_data_type()){
		this->node_data_type = (this->lhs)->get_data_type();
		return true;
	}
	else{
		char err[100];
		sprintf(err, "cs316: Error: Line: %d: Arithmetic statement data type not compatible", this->lineno);
		yyerror(err);
		exit(-1);
	}
}
void Arithmetic_Expr_Ast::print(ostream & file_buffer){
	char assgn_str[] = "\n            Arith:\n";
	int str_size = strlen(assgn_str);
	file_buffer.write(assgn_str,str_size);

	lhs_rhs_print2(this->lhs, this->rhs, file_buffer);
}


Plus_Ast::Plus_Ast(Ast * l, Ast * r, int line){
	this->lhs = l;
	this->rhs = r;
	this->lineno = line;
	this->ast_num_child = binary_arity;
}
void Plus_Ast::print(ostream & file_buffer){
	char plus_str[] = "\n            Arith: PLUS\n";
	int str_size = strlen(plus_str);
	file_buffer.write(plus_str,str_size);

	lhs_rhs_print2(this->lhs, this->rhs, file_buffer);
}


Minus_Ast::Minus_Ast(Ast * l, Ast * r, int line){
	this->lhs = l;
	this->rhs = r;
	this->lineno = line;
	this->ast_num_child = binary_arity;
}
void Minus_Ast::print(ostream & file_buffer){
	char minus_str[] = "\n            Arith: MINUS\n";
	int str_size = strlen(minus_str);
	file_buffer.write(minus_str,str_size);

	lhs_rhs_print2(this->lhs, this->rhs, file_buffer);
}


Divide_Ast::Divide_Ast(Ast * l, Ast * r, int line){
	this->lhs = l;
	this->rhs = r;
	this->lineno = line;
	this->ast_num_child = binary_arity;
}
void Divide_Ast::print(ostream & file_buffer){
	char divide_str[] = "\n            Arith: DIV\n";
	int str_size = strlen(divide_str);
	file_buffer.write(divide_str,str_size);

	lhs_rhs_print2(this->lhs, this->rhs, file_buffer);
}


Mult_Ast::Mult_Ast(Ast * l, Ast * r, int line){
	this->lhs = l;
	this->rhs = r;
	this->lineno = line;
	this->ast_num_child = binary_arity;
}
void Mult_Ast::print(ostream & file_buffer){
	char mult_str[] = "\n            Arith: MULT\n";
	int str_size = strlen(mult_str);
	file_buffer.write(mult_str,str_size);

	lhs_rhs_print2(this->lhs, this->rhs, file_buffer);
}


UMinus_Ast::UMinus_Ast(Ast * l, Ast * r, int line){
	this->lhs = l;
	this->rhs = r;
	this->lineno = line;
	this->ast_num_child = unary_arity;
}
void UMinus_Ast::print(ostream & file_buffer){
	char uminus_str[] = "\n            Arith: UMINUS\n";
	int str_size = strlen(uminus_str);
	file_buffer.write(uminus_str,str_size);

	char lhs_start_str[] = "               LHS (";
	str_size = strlen(lhs_start_str);
	file_buffer.write(lhs_start_str,str_size);

	(this->lhs)->print(file_buffer);

	char lhs_end_str[] = ")";
	str_size = strlen(lhs_end_str);
	file_buffer.write(lhs_end_str,str_size);
}


Conditional_Expression_Ast::Conditional_Expression_Ast(Ast* cond, Ast* l, Ast* r, int line){
	this->lhs = l;
	this->rhs = r;
	this->cond = cond;
	this->lineno = line;
	this->ast_num_child = ternary_arity;
	string redundant = get_new_label();
}
Conditional_Expression_Ast::~Conditional_Expression_Ast(){}
void Conditional_Expression_Ast::print(ostream & file_buffer){
	char cond_str[] = "\n         Cond:\n";
	int str_size = strlen(cond_str);
	file_buffer.write(cond_str,str_size);

	char if_else_str[] = "            IF_ELSE";
	str_size = strlen(if_else_str);
	file_buffer.write(if_else_str,str_size);

	(this->cond)->print(file_buffer);
	char newline_str[] = "\n";
	str_size = strlen(newline_str);
	file_buffer.write(newline_str,str_size);
	lhs_rhs_print1(this->lhs, this->rhs, file_buffer);
}


Relational_Expr_Ast::Relational_Expr_Ast(Ast * lhs, Relational_Op rop, Ast * rhs, int line){
	this->lhs_condition = lhs;
	this->rhs_condition = rhs;
	this->rel_op = rop;
	this->lineno = line;
	this->ast_num_child = binary_arity;
}
Relational_Expr_Ast::~Relational_Expr_Ast(){}
Data_Type Relational_Expr_Ast::get_data_type(){
	return this->node_data_type;
}
void Relational_Expr_Ast::set_data_type(Data_Type dt){
	this->node_data_type = dt;
}
bool Relational_Expr_Ast::check_ast(){
	if((this->lhs_condition)->get_data_type() == (this->rhs_condition)->get_data_type()){
		this->node_data_type = (this->lhs_condition)->get_data_type();
		return true;
	}
	else{
		char err[100];
		sprintf(err, "cs316: Error: Line: %d: Relational statement data type not compatible", this->lineno);
		yyerror(err);
		exit(-1);
	}
}
void Relational_Expr_Ast::print(ostream & file_buffer){
	char cond_str[] = "\n            Condition: ";
	int str_size = strlen(cond_str);
	file_buffer.write(cond_str,str_size);

	if(this->rel_op == less_than){
		file_buffer << "LT\n";
	}
	else if(this->rel_op == less_equalto){
		file_buffer << "LE\n";
	}
	else if(this->rel_op == greater_than){
		file_buffer << "GT\n";
	}
	else if(this->rel_op == greater_equalto){
		file_buffer << "GE\n";
	}
	else if(this->rel_op == equalto){
		file_buffer << "EQ\n";
	}
	else if(this->rel_op == not_equalto){
		file_buffer << "NE\n";
	}
	lhs_rhs_print2(this->lhs_condition, this->rhs_condition, file_buffer);
}


Logical_Expr_Ast::Logical_Expr_Ast(Ast * lhs, Logical_Op bop, Ast * rhs, int line){
	this->lhs_op = lhs;
	this->rhs_op = rhs;
	this->bool_op = bop;
	this->lineno = line;
	this->ast_num_child = binary_arity;
}
Logical_Expr_Ast::~Logical_Expr_Ast(){}
Data_Type Logical_Expr_Ast::get_data_type(){
	return this->node_data_type;
}
void Logical_Expr_Ast::set_data_type(Data_Type dt){
	this->node_data_type = dt;
}
bool Logical_Expr_Ast::check_ast(){
	this->node_data_type = (this->rhs_op)->get_data_type();
	return true;
}
void Logical_Expr_Ast::print(ostream & file_buffer){
	char cond_str[] = "\n            Condition: ";
	int str_size = strlen(cond_str);
	file_buffer.write(cond_str,str_size);

	if(this->bool_op == _logical_not){
		file_buffer << "NOT\n";
		char lhs_start_str[] = "               RHS (";
		int str_size = strlen(lhs_start_str);
		file_buffer.write(lhs_start_str,str_size);

		(this->rhs_op)->print(file_buffer);

		char lhs_end_str[] = ")";
		str_size = strlen(lhs_end_str);
		file_buffer.write(lhs_end_str,str_size);
	}
	else if(this->bool_op == _logical_or){
		file_buffer << "OR\n";
		lhs_rhs_print2(this->lhs_op, this->rhs_op, file_buffer);
	}
	else if(this->bool_op == _logical_and){
		file_buffer << "AND\n";
		lhs_rhs_print2(this->lhs_op, this->rhs_op, file_buffer);

	}
}


Selection_Statement_Ast::Selection_Statement_Ast(Ast* cond,Ast* then_part, Ast* else_part, int line){
	this->cond = cond;
	this->then_part = then_part;
	this->else_part = else_part;
	this->lineno = line;
	this->ast_num_child = ternary_arity;
	// string redundant = get_new_label();
}
Selection_Statement_Ast::~Selection_Statement_Ast(){}
Data_Type Selection_Statement_Ast::get_data_type(){
	return this->node_data_type;
}
void Selection_Statement_Ast::set_data_type(Data_Type dt){
	this->node_data_type = dt;
}
bool Selection_Statement_Ast::check_ast(){
	
}
void Selection_Statement_Ast::print(ostream & file_buffer){
	char if_str[] = "\n         IF : ";
	int str_size = strlen(if_str);
	file_buffer.write(if_str,str_size);

	char cond_str[] = "\n         CONDITION (";
	str_size = strlen(cond_str);
	file_buffer.write(cond_str,str_size);

	(this->cond)->print(file_buffer);

	char cond_end_str[] = ")";
	str_size = strlen(cond_end_str);
	file_buffer.write(cond_end_str,str_size);

	char then_str[] = "\n         THEN (";
	str_size = strlen(then_str);
	file_buffer.write(then_str,str_size);

	(this->then_part)->print(file_buffer);

	char then_end_str[] = ")";
	str_size = strlen(then_end_str);
	file_buffer.write(then_end_str,str_size);

	if(this->else_part != NULL){
		char else_str[] = "\n         ELSE (";
		str_size = strlen(else_str);
		file_buffer.write(else_str,str_size);
		
		(this->else_part)->print(file_buffer);

		char else_end_str[] = ")";
		str_size = strlen(else_end_str);
		file_buffer.write(else_end_str,str_size);
	}
}


Iteration_Statement_Ast::Iteration_Statement_Ast(Ast * cond, Ast* body, int line, bool do_form){
	this->cond = cond;
	this->body = body;
	this->is_do_form = do_form;
	this->lineno = line;
	this->ast_num_child = binary_arity;
	// string redundant = get_new_label();
}
Iteration_Statement_Ast::~Iteration_Statement_Ast(){}
Data_Type Iteration_Statement_Ast::get_data_type(){
	return this->node_data_type;
}
void Iteration_Statement_Ast::set_data_type(Data_Type dt){
	this->node_data_type = dt;
}
bool Iteration_Statement_Ast::check_ast(){

}
void Iteration_Statement_Ast::print(ostream & file_buffer){
	if(this->is_do_form){
		char do_str[] = "\n         DO (";
		int str_size = strlen(do_str);
		file_buffer.write(do_str,str_size);

		(this->body)->print(file_buffer);

		char body_end_str[] = ")";
		str_size = strlen(body_end_str);
		file_buffer.write(body_end_str,str_size);

		char while_str[] = "\n         WHILE CONDITION (";
		str_size = strlen(while_str);
		file_buffer.write(while_str,str_size);

		(this->cond)->print(file_buffer);

		char cond_end_str[] = ")";
		str_size = strlen(cond_end_str);
		file_buffer.write(cond_end_str,str_size);
	}
	else{
		char while_str[] = "\n         WHILE : ";
		int str_size = strlen(while_str);
		file_buffer.write(while_str,str_size);

		char cond_str[] = "\n         CONDITION (";
		str_size = strlen(cond_str);
		file_buffer.write(cond_str,str_size);

		(this->cond)->print(file_buffer);

		char cond_end_str[] = ")";
		str_size = strlen(cond_end_str);
		file_buffer.write(cond_end_str,str_size);

		char body_str[] = "\n         BODY (";
		str_size = strlen(body_str);
		file_buffer.write(body_str,str_size);

		(this->body)->print(file_buffer);

		char body_end_str[] = ")";
		str_size = strlen(body_end_str);
		file_buffer.write(body_end_str,str_size);
	}
}


Sequence_Ast::Sequence_Ast(int line){
	this->lineno = line;
	string redundant = get_new_label();
}
Sequence_Ast::~Sequence_Ast(){}
void Sequence_Ast::ast_push_back(Ast * ast){
	(this->statement_list).push_back(ast);
}
void Sequence_Ast::print(ostream & file_buffer){
	for (list<Ast*>::iterator it = (this->statement_list).begin(); it !=(this->statement_list).end(); ++it){
		char space_str[] = "\n            ";
		int str_size = strlen(space_str);
		file_buffer.write(space_str,str_size);
		(*it)->print(file_buffer);
	}
}


Print_Ast::Print_Ast(Ast *v, int line){
	this->var = v;
	this->lineno = line;
}
Print_Ast::~Print_Ast(){}
void Print_Ast::print(ostream & file_buffer){
	char assgn_str[] = "\n         Print :\n               (";
	int str_size = strlen(assgn_str);
	file_buffer.write(assgn_str,str_size);

	(this->var)->print(file_buffer);

	char rhs_end_str[] = ")";
	str_size = strlen(rhs_end_str);
	file_buffer.write(rhs_end_str,str_size);
}


Call_Ast::Call_Ast(string name, int line){
	this->procedure_name = name;
	this->lineno = line;
	Procedure *procedure = program_object.get_procedure_prototype(name);
	Data_Type retr_type = procedure->get_return_type();
	this->node_data_type = retr_type;
}
Call_Ast::~Call_Ast(){}
Data_Type Call_Ast::get_data_type(){
	return this->node_data_type;
}
void Call_Ast::set_register(Register_Descriptor * reg){
	this->return_value_reg = reg;
}
void Call_Ast::check_actual_formal_param(Symbol_Table & formal_param_list){
	list<Symbol_Table_Entry *> defined_param_list = formal_param_list.get_table();
	if(!actual_param_list.size() == defined_param_list.size()){
		char err[100];
		sprintf(err, "cs316: Error: Line: %d: Actual and formal parameter count do not match", this->lineno);
		yyerror(err);
		exit(-1);
	}
	list<Ast*>::iterator it2 = (this->actual_param_list).begin();
	for (list<Symbol_Table_Entry*>::iterator it1 = defined_param_list.begin(); it1 != defined_param_list.end(); ++it1){
		Data_Type dt1 = (*it1)->get_data_type();
		Data_Type dt2 = (*it2)->get_data_type();
		if(dt1 != dt2){
			char err[100];
			sprintf(err, "cs316: Error: Line: %d: Actual and formal parameters data types are not matching", this->lineno);
			yyerror(err);
			exit(-1);
		}
		++it2;
	}
}
void Call_Ast::set_actual_param_list(list<Ast *> & param_list){
	this->actual_param_list = param_list;
}
void Call_Ast::print(ostream & file_buffer){
	file_buffer << "\n         FN CALL: ";
	file_buffer << this->procedure_name;
	file_buffer << "(";
	for (list<Ast*>::iterator it = (this->actual_param_list).begin(); it != (this->actual_param_list).end(); ++it){
		file_buffer << "\n            ";
		(*it)->print(file_buffer);
	}
	file_buffer << ")";
}


Return_Ast::Return_Ast(Ast * ret_val, string name, int line){
	this->return_value = ret_val;
	this->proc_name = name;
	this->lineno = line;
	if(ret_val == NULL){
		this->node_data_type = void_data_type;
	}
	else{
		this->node_data_type = ret_val->get_data_type();
	}
}
Return_Ast::~Return_Ast(){}
Data_Type Return_Ast::get_data_type(){
	return this->node_data_type;	
}
void Return_Ast::print(ostream & file_buffer){
	file_buffer << "\n         RETURN ";
	if((this->return_value) == NULL){
		file_buffer << "<NOTHING>";
	}
	else{
		(this->return_value)->print(file_buffer);
	}
	file_buffer << "\n";
}