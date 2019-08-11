template class Const_Opd<double>;
template class Const_Opd<int>;


Instruction_Descriptor::Instruction_Descriptor (Tgt_Op op, string name, string mnn, string ics, Icode_Format icf, Assembly_Format af)
{
	this->inst_op = op;
	this->name = name;
	this->mnemonic = mnn;
	this->ic_symbol = ics;
	this->ic_format = icf;
	this->assem_format = af;
}
Instruction_Descriptor::Instruction_Descriptor(){}
Tgt_Op Instruction_Descriptor::get_op(){
	return this->inst_op;
}
string Instruction_Descriptor::get_name(){
	return this->name;	
}
string Instruction_Descriptor::get_mnemonic(){
	return this->mnemonic;
}
string Instruction_Descriptor::get_ic_symbol(){
	return this->ic_symbol;
}
Icode_Format Instruction_Descriptor::get_ic_format(){
	return this->ic_format;
}
Assembly_Format Instruction_Descriptor::get_assembly_format(){
	return this->assem_format;
}
void Instruction_Descriptor::print_instruction_descriptor(ostream & file_buffer){
	// printf("print_instruction_descriptor\n");
	string op_name = this->name;
	file_buffer << "\t";
	file_buffer << op_name;
}


Register_Descriptor * Ics_Opd::get_reg(){}


Mem_Addr_Opd::Mem_Addr_Opd(Symbol_Table_Entry & se){
	this->symbol_entry = &se;
}
void Mem_Addr_Opd::print_ics_opd(ostream & file_buffer){
	// printf("Mem_Addr_Opd::print_ics_opd\n");
	string var_name = (this->symbol_entry)->get_variable_name();
	file_buffer << var_name;
	// file_buffer << "_";
}
void Mem_Addr_Opd::print_asm_opd(ostream & file_buffer){
	if((this->symbol_entry)->get_symbol_scope() != global){
		int offset = (this->symbol_entry)->get_start_offset();
		file_buffer << offset;
		Offset_With_Ref_To ref_off = (this->symbol_entry)->get_ref_offset();
		if(ref_off == fp_ref){
			file_buffer << "($fp)";
		}
		else if(ref_off == sp_ref){
			file_buffer << "($sp)";
		}
	}
	else if((this->symbol_entry)->get_symbol_scope() == global){
		string var_name = (this->symbol_entry)->get_variable_name();
		file_buffer << var_name;
	}
}
Mem_Addr_Opd & Mem_Addr_Opd::operator= (const Mem_Addr_Opd & rhs){
	this->symbol_entry = rhs.symbol_entry;
}


Register_Addr_Opd::Register_Addr_Opd(Register_Descriptor * rd){
	this->register_description = rd;
}
Register_Descriptor * Register_Addr_Opd::get_reg(){
	return this->register_description;
}
void Register_Addr_Opd::print_ics_opd(ostream & file_buffer){
	// printf("Register_Addr_Opd::print_ics_opd\n");
	string reg_name = (this->register_description)->get_name();
	file_buffer << reg_name;
}
void Register_Addr_Opd::print_asm_opd(ostream & file_buffer){
	file_buffer << "$";
	string reg_name = (this->register_description)->get_name();
	file_buffer << reg_name;
}
Register_Addr_Opd & Register_Addr_Opd::operator=(const Register_Addr_Opd & rhs){
	this->register_description = rhs.register_description;
}


template <class T>
Const_Opd<T>::Const_Opd (T num){
	this->num = num;
}
template <class T>
void Const_Opd<T>::print_ics_opd(ostream & file_buffer){
	// string var_name = (this->symbol_entry)->get_variable_name();
	file_buffer << this->num;
}
template <class T>
void Const_Opd<T>::print_asm_opd(ostream & file_buffer){
	file_buffer << this->num;
}
template <class T>
Const_Opd<T> & Const_Opd<T>::operator=(const Const_Opd & rhs){
	this->num = rhs.num;
}


Instruction_Descriptor & Icode_Stmt::get_op(){
	return this->op_desc;
}
Ics_Opd * Icode_Stmt::get_opd1(){}
Ics_Opd * Icode_Stmt::get_opd2(){}
Ics_Opd * Icode_Stmt::get_result(){}
void Icode_Stmt::set_opd1(Ics_Opd * io){}
void Icode_Stmt::set_opd2(Ics_Opd * io){}
void Icode_Stmt::set_result(Ics_Opd * io){}


Print_IC_Stmt::Print_IC_Stmt(){
	this->op_desc = *(machine_desc_object.spim_instruction_table)[print];
}
Print_IC_Stmt::~Print_IC_Stmt(){}
void Print_IC_Stmt::print_icode(ostream &file_buffer){
	(this->op_desc).print_instruction_descriptor(file_buffer);
	file_buffer << "\n";
}
void Print_IC_Stmt::print_assembly(ostream &file_buffer){
	file_buffer << "\t";
	string op_mnn = (this->op_desc).get_mnemonic();
	file_buffer << op_mnn;
	// file_buffer << " ";
	file_buffer << "\n";
}


Move_IC_Stmt::Move_IC_Stmt(Tgt_Op inst_op, Ics_Opd * opd1, Ics_Opd * result){
	this->op_desc = *(machine_desc_object.spim_instruction_table)[inst_op];
	this->opd1 = opd1;
	this->result = result;
}
Move_IC_Stmt & Move_IC_Stmt::operator=(const Move_IC_Stmt & rhs){
	this->op_desc = rhs.op_desc;
	this->opd1 = rhs.opd1;
	this->result = rhs.result;
}
Instruction_Descriptor & Move_IC_Stmt::get_inst_op_of_ics(){
	return this->op_desc;
}
Ics_Opd * Move_IC_Stmt::get_opd1(){
	return this->opd1;
}
void Move_IC_Stmt::set_opd1(Ics_Opd * io){
	this->opd1 = io;
}
Ics_Opd * Move_IC_Stmt::get_result(){
	return this->result;
}
void Move_IC_Stmt::set_result(Ics_Opd * io){
	this->result = io;
}
void Move_IC_Stmt::print_icode(ostream & file_buffer){
	(this->op_desc).print_instruction_descriptor(file_buffer);
	file_buffer << ":    \t";
	(this->result)->print_ics_opd(file_buffer);
	file_buffer << " <- ";
	(this->opd1)->print_ics_opd(file_buffer);
	file_buffer << "\n";
}
void Move_IC_Stmt::print_assembly(ostream & file_buffer){
	// printf("Move_IC_Stmt::print_assembly\n");
	file_buffer << "\t";
	string op_mnn = (this->op_desc).get_mnemonic();
	file_buffer << op_mnn;
	file_buffer << " ";
	if((this->op_desc).get_assembly_format() == a_op_o1_r){
		(this->opd1)->print_asm_opd(file_buffer);
		file_buffer << ", ";
		(this->result)->print_asm_opd(file_buffer);
	}
	else{
		(this->result)->print_asm_opd(file_buffer);
		file_buffer << ", ";
		(this->opd1)->print_asm_opd(file_buffer);
	}
	file_buffer << "\n";
}


Compute_IC_Stmt::Compute_IC_Stmt(Tgt_Op inst_op, Ics_Opd * opd1, Ics_Opd * opd2, Ics_Opd * result)
{
	this->op_desc = *(machine_desc_object.spim_instruction_table)[inst_op];
	this->opd1 = opd1;
	this->opd2 = opd2;
	this->result = result;
}
Compute_IC_Stmt & Compute_IC_Stmt::operator=(const Compute_IC_Stmt & rhs){
	this->op_desc = rhs.op_desc;
	this->opd1 = rhs.opd1;
	this->opd2 = rhs.opd2;
	this->result = rhs.result;
}
Instruction_Descriptor & Compute_IC_Stmt::get_inst_op_of_ics(){
	return this->op_desc;
}
Ics_Opd * Compute_IC_Stmt::get_opd1(){
	return this->opd1;
}
void Compute_IC_Stmt::set_opd1(Ics_Opd * io){
	this->opd1 = io;
}
Ics_Opd * Compute_IC_Stmt::get_opd2(){
	return this->opd2;
}
void Compute_IC_Stmt::set_opd2(Ics_Opd * io){
	this->opd2 = io;
}
Ics_Opd * Compute_IC_Stmt::get_result(){
	return this->result;
}
void Compute_IC_Stmt::set_result(Ics_Opd * io){
	this->result = io;
}
void Compute_IC_Stmt::print_icode(ostream & file_buffer){
	if((this->result)->get_reg()->get_register() != sp){
		(this->op_desc).print_instruction_descriptor(file_buffer);
		file_buffer << ":    \t";
		if((this->op_desc).get_ic_format() == i_o1_op_o2){
			file_buffer << " c1";
		}
		else{
			(this->result)->print_ics_opd(file_buffer);
		}
		file_buffer << " <- ";
		(this->opd1)->print_ics_opd(file_buffer);
		file_buffer << " , ";
		(this->opd2)->print_ics_opd(file_buffer);
		file_buffer << "\n";	
	}
}
void Compute_IC_Stmt::print_assembly(ostream & file_buffer){
	file_buffer << "\t";
	string op_mnn = (this->op_desc).get_mnemonic();
	file_buffer << op_mnn;
	file_buffer << " ";
	if((this->op_desc).get_assembly_format() != a_op_o1_o2){
		(this->result)->print_asm_opd(file_buffer);
		file_buffer << ", ";
	}
	(this->opd1)->print_asm_opd(file_buffer);
	file_buffer << ", ";
	(this->opd2)->print_asm_opd(file_buffer);
	file_buffer << "\n";
}


Control_Flow_IC_Stmt::Control_Flow_IC_Stmt(Tgt_Op op, Ics_Opd * o1, Ics_Opd * o2, string label, int size){
	this->op_desc = *(machine_desc_object.spim_instruction_table)[op];
	this->opd1 = o1;
	this->opd2 = o2;
	this->offset = label;
	this->actual_param_size = size;
}
Control_Flow_IC_Stmt & Control_Flow_IC_Stmt::operator=(const Control_Flow_IC_Stmt & rhs){
	this->op_desc = rhs.op_desc;
	this->opd1 = rhs.opd1;
	this->opd2 = rhs.opd2;
	this->offset = rhs.offset;
	this->actual_param_size = rhs.actual_param_size;
}
Instruction_Descriptor & Control_Flow_IC_Stmt::get_inst_op_of_ics(){
	return this->op_desc;
}
Ics_Opd * Control_Flow_IC_Stmt::get_opd1(){
	return this->opd1;
}
void Control_Flow_IC_Stmt::set_opd1(Ics_Opd * io){
	this->opd1 = io;
}
Ics_Opd * Control_Flow_IC_Stmt::get_opd2(){
	return this->opd2;
}
void Control_Flow_IC_Stmt::set_opd2(Ics_Opd * io){
	this->opd2 = io;
}
string Control_Flow_IC_Stmt::get_Offset(){
	return this->offset;
}
void Control_Flow_IC_Stmt::set_Offset(string label){
	this->offset = label;
}
void Control_Flow_IC_Stmt::print_icode(ostream & file_buffer){
	(this->op_desc).print_instruction_descriptor(file_buffer);
	file_buffer << ":    \t";
	(this->opd1)->print_ics_opd(file_buffer);
	file_buffer << " , ";
	(this->opd2)->print_ics_opd(file_buffer);
	file_buffer << " : goto ";
	file_buffer << (this->offset);
	file_buffer << "\n";
}
void Control_Flow_IC_Stmt::print_assembly(ostream & file_buffer){
	file_buffer << "\t";
	string op_mnn = (this->op_desc).get_mnemonic();
	file_buffer << op_mnn;
	file_buffer << " ";
	(this->opd1)->print_asm_opd(file_buffer);
	file_buffer << ", ";
	(this->opd2)->print_asm_opd(file_buffer);
	file_buffer << ", ";
	file_buffer << (this->offset);
	file_buffer << " ";
	file_buffer << "\n";
}


Label_IC_Stmt::Label_IC_Stmt(Tgt_Op inst_op, string label){
	this->op_desc = *(machine_desc_object.spim_instruction_table)[inst_op];
	this->label = label;
}
Label_IC_Stmt & Label_IC_Stmt::operator=(const Label_IC_Stmt & rhs){
	this->op_desc = rhs.op_desc;
}
Instruction_Descriptor & Label_IC_Stmt::get_inst_op_of_ics(){
	return this->op_desc;
}
string Label_IC_Stmt::get_label(){
	return this->label;
}
void Label_IC_Stmt::set_label(string label){
	this->label = label;
}
void Label_IC_Stmt::print_icode(ostream & file_buffer){
	if((this->op_desc).get_op() == bc1f || (this->op_desc).get_op() == bc1t){
		(this->op_desc).print_instruction_descriptor(file_buffer);
		file_buffer << " ";
		file_buffer << this->label;
	}
	else if((this->op_desc).get_op() == ret_inst){
		(this->op_desc).print_instruction_descriptor(file_buffer);
		// file_buffer << this->label;
	}
	else if((this->op_desc).get_op() == jal){
		file_buffer << "\t";
		file_buffer << "call";
		file_buffer << " ";
		file_buffer << this->label;
	}
	else if((this->op_desc).get_name() == ""){
		file_buffer << "\n";
		file_buffer << this->label;
		file_buffer << ":    \t";
	}
	else{
		file_buffer << "\t";
		file_buffer << "goto ";
		file_buffer << this->label;
	}
	file_buffer << "\n";
}
void Label_IC_Stmt::print_assembly(ostream & file_buffer){
	if((this->op_desc).get_op() == ret_inst){
		file_buffer << "\t";
		file_buffer << "j";
		file_buffer << " ";
		file_buffer << this->label;
		file_buffer << "\n";
	}
	else if((this->op_desc).get_mnemonic() == ""){
		file_buffer << "\n";
		file_buffer << this->label;
		file_buffer << ":    \t";
		file_buffer << "\n";
	}
	else{
		file_buffer << "\t";
		string op_mnn = (this->op_desc).get_mnemonic();
		file_buffer << op_mnn;
		file_buffer << " ";
		file_buffer << this->label;
		// if((this->op_desc).get_op() == bc1f || (this->op_desc).get_op() == bc1t){
		// 	file_buffer << " ";
		// }
		file_buffer << "\n";
	}
}


Code_For_Ast::Code_For_Ast(){}
Code_For_Ast::Code_For_Ast(list<Icode_Stmt *> & ic_l, Register_Descriptor * reg){
	this->ics_list = ic_l;
	this->result_register = reg;
}
void Code_For_Ast::append_ics(Icode_Stmt & ics){
	(this->ics_list).push_back(&ics);
}
list<Icode_Stmt *> & Code_For_Ast::get_icode_list(){
	return this->ics_list;
}
Register_Descriptor * Code_For_Ast::get_reg(){
	return this->result_register;
}
void Code_For_Ast::set_reg(Register_Descriptor * reg){
	this->result_register = reg;
}
Code_For_Ast & Code_For_Ast::operator=(const Code_For_Ast & rhs){
	this->ics_list = rhs.ics_list;
	this->result_register = rhs.result_register;
}