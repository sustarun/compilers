extern "C" void yyerror (char *s);

// Remove Below
Local_Environment interpreter_global_table;

Eval_Result & Program::evaluate(){

}
// Remove Above

template class Number_Ast<double>;
template class Number_Ast<int>;

void Ast::print_value(Local_Environment & eval_env, ostream & file_buffer){

}
Eval_Result & Ast::get_value_of_evaluation(Local_Environment & eval_env){

}
void Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result){

}


Eval_Result & Assignment_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	// printf("In Assignment_Ast::evaluate\n");
	Eval_Result *eval_result = &(this->rhs)->evaluate(eval_env, file_buffer);
	this->print(file_buffer);
	eval_result->set_variable_status(true);
	string name = ((this->lhs)->get_symbol_entry()).get_variable_name();
	if(eval_env.does_variable_exist(name)){
		(this->lhs)->set_value_of_evaluation(eval_env, *eval_result);
		(this->lhs)->print_value(eval_env, file_buffer);
	}
	else if(interpreter_global_table.does_variable_exist(name)){
		(this->lhs)->set_value_of_evaluation(interpreter_global_table, *eval_result);
		(this->lhs)->print_value(interpreter_global_table, file_buffer);
	}
	else{
		char err[100];
		sprintf(err, "cs316: Error: Line: %d: Variable has not been declared", this->lineno);
		yyerror(err);
		exit(-1);
	}
	return *eval_result;
}


void Name_Ast::print_value(Local_Environment & eval_env, ostream & file_buffer){
	file_buffer << "\n"<<AST_SPACE;
	string name = (this->get_symbol_entry()).get_variable_name();
	file_buffer << name << " : ";
	if(this->get_data_type() == int_data_type){
		int value = (eval_env.get_variable_value(name))->get_int_value();
		file_buffer << value;
	}
	else if(this->get_data_type() == double_data_type){
		double value = (eval_env.get_variable_value(name))->get_double_value();
		file_buffer << value;
	}
	file_buffer << "\n\n";
}
Eval_Result & Name_Ast::get_value_of_evaluation(Local_Environment & eval_env){
	string name = (this->get_symbol_entry()).get_variable_name();
	if(eval_env.does_variable_exist(name)){
		if(eval_env.is_variable_defined(name)){
			Eval_Result *eval_result = eval_env.get_variable_value(name);
			return *eval_result;
		}
		else{
			char err[100];
			sprintf(err, "cs316: Error: Line: %d: Variable should be defined before its use", this->lineno);
			yyerror(err);
			exit(-1);
		}
	}
	else if(interpreter_global_table.does_variable_exist(name)){
		if(interpreter_global_table.is_variable_defined(name)){
			Eval_Result *eval_result = interpreter_global_table.get_variable_value(name);
			return *eval_result;
		}
		else{
			char err[100];
			sprintf(err, "cs316: Error: Line: %d: Variable should be defined before its use", this->lineno);
			yyerror(err);
			exit(-1);
		}
	}
	else{
		char err[100];
		sprintf(err, "cs316: Error: Line: %d: Variable has not been declared", this->lineno);
		yyerror(err);
		exit(-1);
	}
}
void Name_Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result){
	string name = (this->get_symbol_entry()).get_variable_name();
	eval_env.put_variable_value(result,name);
}
Eval_Result & Name_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	return this->get_value_of_evaluation(eval_env);
}


template <class T>
Eval_Result & Number_Ast<T>::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(this->get_data_type() == int_data_type){
		Eval_Result_Value_Int *eval_result = new Eval_Result_Value_Int();
		// eval_result->set_variable_status(false);
		eval_result->set_value(this->constant);
		eval_result->set_result_enum(int_result);
		return *eval_result;
	}
	else if(this->get_data_type() == double_data_type){
		Eval_Result_Value_Double *eval_result = new Eval_Result_Value_Double();
		// eval_result->set_variable_status(false);
		eval_result->set_value(this->constant);
		eval_result->set_result_enum(double_result);
		return *eval_result;
	}
}


Eval_Result & Arithmetic_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){

}


Eval_Result & Plus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	Eval_Result *eval_result_lhs = &(this->lhs)->evaluate(eval_env, file_buffer);
	Eval_Result *eval_result_rhs = &(this->rhs)->evaluate(eval_env, file_buffer);
	if(eval_result_lhs->get_result_enum() == int_result && eval_result_rhs->get_result_enum() == int_result){
		int lhs_value = eval_result_lhs->get_int_value();
		int rhs_value = eval_result_rhs->get_int_value();
		Eval_Result_Value_Int *eval_result = new Eval_Result_Value_Int();
		// eval_result->set_variable_status(false);
		eval_result->set_value(lhs_value + rhs_value);
		eval_result->set_result_enum(int_result);
		return *eval_result;
	}
	else if(eval_result_lhs->get_result_enum() == double_result && eval_result_rhs->get_result_enum() == double_result){
		double lhs_value = eval_result_lhs->get_double_value();
		double rhs_value = eval_result_rhs->get_double_value();
		Eval_Result_Value_Double *eval_result = new Eval_Result_Value_Double();
		// eval_result->set_variable_status(false);
		eval_result->set_value(lhs_value + rhs_value);
		eval_result->set_result_enum(double_result);
		return *eval_result;
	}
	else{
		char err[100];
		sprintf(err, "cs316: Error: Line: %d: Arithmetic evaluation data type not compatible", this->lineno);
		yyerror(err);
		exit(-1);
	}
}


Eval_Result & Minus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	Eval_Result *eval_result_lhs = &(this->lhs)->evaluate(eval_env, file_buffer);
	Eval_Result *eval_result_rhs = &(this->rhs)->evaluate(eval_env, file_buffer);
	if(eval_result_lhs->get_result_enum() == int_result && eval_result_rhs->get_result_enum() == int_result){
		int lhs_value = eval_result_lhs->get_int_value();
		int rhs_value = eval_result_rhs->get_int_value();
		Eval_Result_Value_Int *eval_result = new Eval_Result_Value_Int();
		// eval_result->set_variable_status(false);
		eval_result->set_value(lhs_value - rhs_value);
		eval_result->set_result_enum(int_result);
		return *eval_result;
	}
	else if(eval_result_lhs->get_result_enum() == double_result && eval_result_rhs->get_result_enum() == double_result){
		double lhs_value = eval_result_lhs->get_double_value();
		double rhs_value = eval_result_rhs->get_double_value();
		Eval_Result_Value_Double *eval_result = new Eval_Result_Value_Double();
		// eval_result->set_variable_status(false);
		eval_result->set_value(lhs_value - rhs_value);
		eval_result->set_result_enum(double_result);
		return *eval_result;
	}
	else{
		char err[100];
		sprintf(err, "cs316: Error: Line: %d: Arithmetic evaluation data type not compatible", this->lineno);
		yyerror(err);
		exit(-1);
	}
}


Eval_Result & Divide_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	Eval_Result *eval_result_lhs = &(this->lhs)->evaluate(eval_env, file_buffer);
	Eval_Result *eval_result_rhs = &(this->rhs)->evaluate(eval_env, file_buffer);
	if(eval_result_lhs->get_result_enum() == int_result && eval_result_rhs->get_result_enum() == int_result){
		int lhs_value = eval_result_lhs->get_int_value();
		int rhs_value = eval_result_rhs->get_int_value();
		Eval_Result_Value_Int *eval_result = new Eval_Result_Value_Int();
		// eval_result->set_variable_status(false);
		if(rhs_value == 0){
			char err[100];
			sprintf(err, "cs316: Error: Line: %d: Divide by 0", this->lineno);
			yyerror(err);
			exit(-1);
		}
		eval_result->set_value(lhs_value / rhs_value);
		eval_result->set_result_enum(int_result);
		return *eval_result;
	}
	else if(eval_result_lhs->get_result_enum() == double_result && eval_result_rhs->get_result_enum() == double_result){
		double lhs_value = eval_result_lhs->get_double_value();
		double rhs_value = eval_result_rhs->get_double_value();
		Eval_Result_Value_Double *eval_result = new Eval_Result_Value_Double();
		// eval_result->set_variable_status(false);
		if(rhs_value == 0.0){
			char err[100];
			sprintf(err, "cs316: Error: Line: %d: Divide by 0", this->lineno);
			yyerror(err);
			exit(-1);
		}
		eval_result->set_value(lhs_value / rhs_value);
		eval_result->set_result_enum(double_result);
		return *eval_result;
	}
	else{
		char err[100];
		sprintf(err, "cs316: Error: Line: %d: Arithmetic evaluation data type not compatible", this->lineno);
		yyerror(err);
		exit(-1);
	}
}


Eval_Result & Mult_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	Eval_Result *eval_result_lhs = &(this->lhs)->evaluate(eval_env, file_buffer);
	Eval_Result *eval_result_rhs = &(this->rhs)->evaluate(eval_env, file_buffer);
	if(eval_result_lhs->get_result_enum() == int_result && eval_result_rhs->get_result_enum() == int_result){
		int lhs_value = eval_result_lhs->get_int_value();
		int rhs_value = eval_result_rhs->get_int_value();
		Eval_Result_Value_Int *eval_result = new Eval_Result_Value_Int();
		// eval_result->set_variable_status(false);
		eval_result->set_value(lhs_value * rhs_value);
		eval_result->set_result_enum(int_result);
		return *eval_result;
	}
	else if(eval_result_lhs->get_result_enum() == double_result && eval_result_rhs->get_result_enum() == double_result){
		double lhs_value = eval_result_lhs->get_double_value();
		double rhs_value = eval_result_rhs->get_double_value();
		Eval_Result_Value_Double *eval_result = new Eval_Result_Value_Double();
		// eval_result->set_variable_status(false);
		eval_result->set_value(lhs_value * rhs_value);
		eval_result->set_result_enum(double_result);
		return *eval_result;
	}
	else{
		char err[100];
		sprintf(err, "cs316: Error: Line: %d: Arithmetic evaluation data type not compatible", this->lineno);
		yyerror(err);
		exit(-1);
	}
}


Eval_Result & UMinus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	Eval_Result *eval_result_lhs = &(this->lhs)->evaluate(eval_env, file_buffer);
	if(eval_result_lhs->get_result_enum() == int_result){
		int lhs_value = eval_result_lhs->get_int_value();
		Eval_Result_Value_Int *eval_result = new Eval_Result_Value_Int();
		// eval_result->set_variable_status(false);
		eval_result->set_value(-lhs_value);
		eval_result->set_result_enum(int_result);
		return *eval_result;
	}
	else if(eval_result_lhs->get_result_enum() == double_result){
		double lhs_value = eval_result_lhs->get_double_value();
		Eval_Result_Value_Double *eval_result = new Eval_Result_Value_Double();
		// eval_result->set_variable_status(false);
		eval_result->set_value(-lhs_value);
		eval_result->set_result_enum(double_result);
		return *eval_result;
	}
	else{
		char err[100];
		sprintf(err, "cs316: Error: Line: %d: Arithmetic evaluation data type not compatible", this->lineno);
		yyerror(err);
		exit(-1);
	}
}


Eval_Result & Conditional_Expression_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	Eval_Result *eval_result_cond = &(this->cond)->evaluate(eval_env, file_buffer);
	int cond_value = eval_result_cond->get_int_value();
	if(cond_value == 1){
		Eval_Result *eval_result_lhs = &(this->lhs)->evaluate(eval_env, file_buffer);
		// eval_result_lhs->set_variable_status(false);
		return *eval_result_lhs;
	}
	else if(cond_value == 0){
		Eval_Result *eval_result_rhs = &(this->rhs)->evaluate(eval_env, file_buffer);
		// eval_result_rhs->set_variable_status(false);
		return *eval_result_rhs;
	}
	else{
		char err[100];
		sprintf(err, "cs316: Error: Line: %d: Conditional Expression wrong evaluation", this->lineno);
		yyerror(err);
		exit(-1);
	}
}


Eval_Result & Relational_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	Eval_Result *eval_result_lhs = &(this->lhs_condition)->evaluate(eval_env, file_buffer);
	Eval_Result *eval_result_rhs = &(this->rhs_condition)->evaluate(eval_env, file_buffer);
	int rel_val = 0;
	if(eval_result_lhs->get_result_enum() == int_result && eval_result_rhs->get_result_enum() == int_result){
		int lhs_value = eval_result_lhs->get_int_value();
		int rhs_value = eval_result_rhs->get_int_value();
		if(this->rel_op == less_equalto){
			if(lhs_value <= rhs_value){
				rel_val = 1;
			}
		}
		else if(this->rel_op == less_than){
			if(lhs_value < rhs_value){
				rel_val = 1;
			}
		}
		else if(this->rel_op == greater_than){
			if(lhs_value > rhs_value){
				rel_val = 1;
			}
		}
		else if(this->rel_op == greater_equalto){
			if(lhs_value >= rhs_value){
				rel_val = 1;
			}
		}
		else if(this->rel_op == equalto){
			if(lhs_value == rhs_value){
				rel_val = 1;
			}
		}
		else if(this->rel_op == not_equalto){
			if(lhs_value != rhs_value){
				rel_val = 1;
			}
		}
	}
	else if(eval_result_lhs->get_result_enum() == double_result && eval_result_rhs->get_result_enum() == double_result){
		double lhs_value = eval_result_lhs->get_double_value();
		double rhs_value = eval_result_rhs->get_double_value();
		if(this->rel_op == less_equalto){
			if(lhs_value <= rhs_value){
				rel_val = 1;
			}
		}
		else if(this->rel_op == less_than){
			if(lhs_value < rhs_value){
				rel_val = 1;
			}
		}
		else if(this->rel_op == greater_than){
			if(lhs_value > rhs_value){
				rel_val = 1;
			}
		}
		else if(this->rel_op == greater_equalto){
			if(lhs_value >= rhs_value){
				rel_val = 1;
			}
		}
		else if(this->rel_op == equalto){
			if(lhs_value == rhs_value){
				rel_val = 1;
			}
		}
		else if(this->rel_op == not_equalto){
			if(lhs_value != rhs_value){
				rel_val = 1;
			}
		}
	}
	else{
		char err[100];
		sprintf(err, "cs316: Error: Line: %d: Relational evaluation data type not compatible", this->lineno);
		yyerror(err);
		exit(-1);
	}
	Eval_Result_Value_Int *eval_result = new Eval_Result_Value_Int();
	// eval_result->set_variable_status(false);
	eval_result->set_value(rel_val);
	eval_result->set_result_enum(int_result);
	return *eval_result;
}


Eval_Result & Logical_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	Eval_Result *eval_result_rhs = &(this->rhs_op)->evaluate(eval_env, file_buffer);
	int bool_val = 0;
	int rhs_value = eval_result_rhs->get_int_value();
	if(this->bool_op == _logical_not){
		if(rhs_value == 0){
			bool_val = 1;
		}
	}
	else{
		Eval_Result *eval_result_lhs = &(this->lhs_op)->evaluate(eval_env, file_buffer);
		int lhs_value = eval_result_lhs->get_int_value();
		if(this->bool_op == _logical_or){
			if(lhs_value == 1 || rhs_value == 1){
				bool_val = 1;
			}
		}
		else if(this->bool_op == _logical_and){
			if(lhs_value == 1 && rhs_value == 1){
				bool_val = 1;
			}
		}
	}
	Eval_Result_Value_Int *eval_result = new Eval_Result_Value_Int();
	// eval_result->set_variable_status(false);
	eval_result->set_value(bool_val);
	eval_result->set_result_enum(int_result);
	return *eval_result;
}


Eval_Result & Selection_Statement_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	Eval_Result *eval_result_cond = &(this->cond)->evaluate(eval_env, file_buffer);
	int cond_value = eval_result_cond->get_int_value();
	// printf("cond_value = %d\n", cond_value);
	if(cond_value == 1){
		return (this->then_part)->evaluate(eval_env, file_buffer);
	}
	else if(cond_value == 0){
		if(this->else_part !=NULL){
			return (this->else_part)->evaluate(eval_env, file_buffer);
		}		
	}
	Eval_Result_Value_Int *eval_result = new Eval_Result_Value_Int();
	return *eval_result;
}


Eval_Result & Iteration_Statement_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	Eval_Result *eval_result_cond = &(this->cond)->evaluate(eval_env, file_buffer);
	int cond_value = eval_result_cond->get_int_value();
	Eval_Result *eval_result;
	if(this->is_do_form){
		eval_result = &(this->body)->evaluate(eval_env, file_buffer);
		eval_result_cond = &(this->cond)->evaluate(eval_env, file_buffer);
		cond_value = eval_result_cond->get_int_value();
	}
	while(cond_value == 1){
		eval_result = &(this->body)->evaluate(eval_env, file_buffer);
		eval_result_cond = &(this->cond)->evaluate(eval_env, file_buffer);
		cond_value = eval_result_cond->get_int_value();
	}
	return *eval_result;
}


Eval_Result & Sequence_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	Eval_Result *eval_result;
	for (list<Ast*>::iterator it = (this->statement_list).begin(); it !=(this->statement_list).end(); ++it){
		eval_result = &(*it)->evaluate(eval_env, file_buffer);
	}
	return *eval_result;
}


Eval_Result & Call_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	
}


Eval_Result & Return_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	
}