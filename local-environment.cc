extern "C" void yyerror (char *s);

void Symbol_Table::create(Local_Environment & local_global_variables_table){
	// printf("In Symbol_Table::create function\n");
	for (list<Symbol_Table_Entry*>::iterator it = (this->variable_table).begin(); it !=(this->variable_table).end(); ++it){
		string var_name = (*it)->get_variable_name();
		if((*it)->get_data_type() == int_data_type){
			Eval_Result_Value_Int *eval_result = new Eval_Result_Value_Int();
			if((*it)->get_symbol_scope() == local){
				eval_result->set_variable_status(false);
			}
			else if((*it)->get_symbol_scope() == global){
				eval_result->set_variable_status(true);	
				eval_result->set_value(0);
			}
			eval_result->set_result_enum(int_result);
			local_global_variables_table.put_variable_value(*eval_result, var_name);
		}
		else if((*it)->get_data_type() == double_data_type){
			Eval_Result_Value_Double *eval_result = new Eval_Result_Value_Double();
			if((*it)->get_symbol_scope() == local){
				eval_result->set_variable_status(false);
			}
			else if((*it)->get_symbol_scope() == global){
				eval_result->set_variable_status(true);	
				eval_result->set_value(0.0);
			}
			eval_result->set_result_enum(double_result);
			local_global_variables_table.put_variable_value(*eval_result, var_name);
		}
	}
}


int Eval_Result::get_int_value(){}
void Eval_Result::set_value(int value){}
double Eval_Result::get_double_value(){}
void Eval_Result::set_value(double value){}
bool Eval_Result::is_variable_defined(){}
void Eval_Result::set_variable_status(bool def){}


void Eval_Result_Value::set_value(int number){}
void Eval_Result_Value::set_value(double number){}
int Eval_Result_Value::get_int_value(){}
double Eval_Result_Value::get_double_value(){}


Eval_Result_Value_Int::Eval_Result_Value_Int(){}
Eval_Result_Value_Int::~Eval_Result_Value_Int(){}
void Eval_Result_Value_Int::set_value(int number){
	this->value = number;
}
void Eval_Result_Value_Int::set_value(double number){}
int Eval_Result_Value_Int::get_int_value(){
	return this->value;
}
void Eval_Result_Value_Int::set_variable_status(bool def){
	this->defined = def;
}
bool Eval_Result_Value_Int::is_variable_defined(){
	return this->defined;
}
void Eval_Result_Value_Int::set_result_enum(Result_Enum res){
	this->result_type = res;
}
Result_Enum Eval_Result_Value_Int::get_result_enum(){
	return this->result_type;
}


Eval_Result_Value_Double::Eval_Result_Value_Double(){}
Eval_Result_Value_Double::~Eval_Result_Value_Double(){}
void Eval_Result_Value_Double::set_value(int number){
	
}
void Eval_Result_Value_Double::set_value(double number){
	this->value = number;
}
double Eval_Result_Value_Double::get_double_value(){
	return this->value;
}
void Eval_Result_Value_Double::set_variable_status(bool def){
	this->defined = def;
}
bool Eval_Result_Value_Double::is_variable_defined(){
	return this->defined;
}
void Eval_Result_Value_Double::set_result_enum(Result_Enum res){
	this->result_type = res;
}
Result_Enum Eval_Result_Value_Double::get_result_enum(){
	return this->result_type;
}


Local_Environment::Local_Environment(){
	// printf("In Local_Environment::Local_Environment function\n");
}
Local_Environment::~Local_Environment(){
	// printf("In Local_Environment::~Local_Environment function\n");
}
void Local_Environment::print(ostream & file_buffer){
	// printf("In Local_Environment::print function\n");
	for (map<string,Eval_Result*>::iterator it = (this->variable_table).begin(); it !=(this->variable_table).end(); ++it){
		file_buffer <<VAR_SPACE<< it->first <<" : ";
		Eval_Result *eval_result = it->second;
		if(eval_result->is_variable_defined()){
			if(eval_result->get_result_enum() == int_result){
				file_buffer << eval_result->get_int_value();
			}
			else if(eval_result->get_result_enum() == double_result){
				// cout<<"Float value = "<<eval_result->get_double_value()<<endl;
				file_buffer << eval_result->get_double_value();
			}
		}
		else{
			file_buffer << "undefined";
		}
		file_buffer<<"\n";
	}
}
bool Local_Environment::is_variable_defined(string name){
	// printf("In Local_Environment::is_variable_defined function\n");
	if(this->does_variable_exist(name)){
		return ((this->variable_table)[name])->is_variable_defined();
	}
	else{
		char err[100];
		sprintf(err, "cs316: Error: Variable Does Not Exist");
		yyerror(err);
		exit(-1);
	}
}
Eval_Result * Local_Environment::get_variable_value(string name){
	// printf("In Local_Environment::get_variable_value function\n");
	if(this->is_variable_defined(name)){
		return (this->variable_table)[name];
	}
	else{
		char err[100];
		sprintf(err, "cs316: Error: Variable Not Defined");
		yyerror(err);
		exit(-1);
	}
}
void Local_Environment::put_variable_value(Eval_Result & value, string name){
	// printf("In Local_Environment::put_variable_value function\n");
	// (this->variable_table).insert(pair<string, Eval_Result*>(name,&value));
	(this->variable_table)[name] = &value;
}
bool Local_Environment::does_variable_exist(string name){
	// printf("In Local_Environment::does_variable_exist function\n");
	if((this->variable_table).count(name) == 0){
		return false;
	}
	else{
		return true;
	}
}