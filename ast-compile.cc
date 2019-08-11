extern "C" void yyerror (char *s);

template class Number_Ast<double>;
template class Number_Ast<int>;


Code_For_Ast & Ast::create_store_stmt(Register_Descriptor * store_register){}


Code_For_Ast & Assignment_Ast::compile(){
	// printf("In Assignment_Ast Compile\n");
	Code_For_Ast *rhs_cfa = &(this->rhs)->compile();
	Register_Descriptor * store_reg = rhs_cfa->get_reg();
	
	Code_For_Ast *lhs_cfa = &(this->lhs)->create_store_stmt(store_reg);
	Code_For_Ast *cfa = rhs_cfa;

	list<Icode_Stmt *> ics_list = lhs_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = ics_list.begin(); it != ics_list.end(); ++it){
		cfa->append_ics(*(*it));
	}
	return *cfa;
}
Code_For_Ast & Assignment_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}


Code_For_Ast & Name_Ast::compile(){
	// printf("In Name_Ast Compile\n");
	Code_For_Ast *cfa = new Code_For_Ast();

	Symbol_Table_Entry *se = &(this->get_symbol_entry());
	Mem_Addr_Opd *opd1 = new Mem_Addr_Opd(*se);
	
	Register_Descriptor * result_reg = new Register_Descriptor();
	
	Tgt_Op op;
	if(this->get_data_type() == int_data_type){
		result_reg = machine_desc_object.get_new_register<int_reg>();
		op = load;
	}
	else if(this->get_data_type() == double_data_type){
		result_reg = machine_desc_object.get_new_register<float_reg>();
		op = load_d;
	}

	result_reg->set_use_for_expr_result();
	Register_Addr_Opd *result = new Register_Addr_Opd(result_reg);
	Move_IC_Stmt *move_ics = new Move_IC_Stmt(op, opd1, result);
	cfa->append_ics(*move_ics);
	cfa->set_reg(result_reg);
	return *cfa;
}
Code_For_Ast & Name_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}
Code_For_Ast & Name_Ast::create_store_stmt(Register_Descriptor * store_register){
	Code_For_Ast *cfa = new Code_For_Ast();
	
	Symbol_Table_Entry *se = &(this->get_symbol_entry());
	Mem_Addr_Opd *result = new Mem_Addr_Opd(*se);

	Tgt_Op op;
	if(this->get_data_type() == int_data_type){
		op = store;
	}
	else if(this->get_data_type() == double_data_type){
		op = store_d;
	}

	Register_Addr_Opd *opd1 = new Register_Addr_Opd(store_register);
	store_register->reset_use_for_expr_result();
	Move_IC_Stmt *move_ics = new Move_IC_Stmt(op, opd1, result);
	cfa->append_ics(*move_ics);
	return *cfa;
}


template <class T>
Code_For_Ast & Number_Ast<T>::compile(){
	// printf("In Number_Ast Compile\n");
	Code_For_Ast *cfa = new Code_For_Ast();
	
	Const_Opd<T> *opd1 = new Const_Opd<T>(this->constant);
	
	Register_Descriptor * result_reg = new Register_Descriptor();
	Tgt_Op op;
	if(this->get_data_type() == int_data_type){
		result_reg = machine_desc_object.get_new_register<int_reg>();
		op = imm_load;
	}
	else if(this->get_data_type() == double_data_type){
		result_reg = machine_desc_object.get_new_register<float_reg>();
		op = imm_load_d;
	}	

	result_reg->set_use_for_expr_result();
	Register_Addr_Opd *result = new Register_Addr_Opd(result_reg);
	Move_IC_Stmt *move_ics = new Move_IC_Stmt(op, opd1, result);
	cfa->append_ics(*move_ics);
	cfa->set_reg(result_reg);
	return *cfa;

}
template <class T>
Code_For_Ast & Number_Ast<T>::compile_and_optimize_ast(Lra_Outcome & lra){}


Code_For_Ast & Plus_Ast::compile(){
	Code_For_Ast *cfa = new Code_For_Ast();
	
	Code_For_Ast *lhs_cfa = &(this->lhs)->compile();
	Code_For_Ast *rhs_cfa = &(this->rhs)->compile();

	list<Icode_Stmt *> lhs_ics_list = lhs_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = lhs_ics_list.begin(); it != lhs_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
	}

	list<Icode_Stmt *> rhs_ics_list = rhs_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = rhs_ics_list.begin(); it != rhs_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
	}
	
	Register_Addr_Opd *opd1 = new Register_Addr_Opd(lhs_cfa->get_reg());
	Register_Addr_Opd *opd2 = new Register_Addr_Opd(rhs_cfa->get_reg());

	Register_Descriptor * result_reg = new Register_Descriptor();
	Tgt_Op op;
	if(this->get_data_type() == int_data_type){
		result_reg = machine_desc_object.get_new_register<int_reg>();
		op = add;
	}
	else if(this->get_data_type() == double_data_type){
		result_reg = machine_desc_object.get_new_register<float_reg>();
		op = add_d;
	}
	
	result_reg->set_use_for_expr_result();
	Register_Addr_Opd *result = new Register_Addr_Opd(result_reg);
	Compute_IC_Stmt *comp_ics = new Compute_IC_Stmt(op, opd1, opd2, result);
	cfa->append_ics(*comp_ics);
	lhs_cfa->get_reg()->reset_use_for_expr_result();
	rhs_cfa->get_reg()->reset_use_for_expr_result();
	cfa->set_reg(result_reg);
	return *cfa;
}
Code_For_Ast & Plus_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}


Code_For_Ast & Minus_Ast::compile(){
	Code_For_Ast *cfa = new Code_For_Ast();
	
	Code_For_Ast *lhs_cfa = &(this->lhs)->compile();
	Code_For_Ast *rhs_cfa = &(this->rhs)->compile();

	list<Icode_Stmt *> lhs_ics_list = lhs_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = lhs_ics_list.begin(); it != lhs_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
	}

	list<Icode_Stmt *> rhs_ics_list = rhs_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = rhs_ics_list.begin(); it != rhs_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
	}
	
	Register_Addr_Opd *opd1 = new Register_Addr_Opd(lhs_cfa->get_reg());
	Register_Addr_Opd *opd2 = new Register_Addr_Opd(rhs_cfa->get_reg());

	Register_Descriptor * result_reg = new Register_Descriptor();
	Tgt_Op op;
	if(this->get_data_type() == int_data_type){
		result_reg = machine_desc_object.get_new_register<int_reg>();
		op = sub;
	}
	else if(this->get_data_type() == double_data_type){
		result_reg = machine_desc_object.get_new_register<float_reg>();
		op = sub_d;
	}

	result_reg->set_use_for_expr_result();
	Register_Addr_Opd *result = new Register_Addr_Opd(result_reg);
	Compute_IC_Stmt *comp_ics = new Compute_IC_Stmt(op, opd1, opd2, result);
	cfa->append_ics(*comp_ics);
	lhs_cfa->get_reg()->reset_use_for_expr_result();
	rhs_cfa->get_reg()->reset_use_for_expr_result();
	cfa->set_reg(result_reg);
	return *cfa;
}
Code_For_Ast & Minus_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}


Code_For_Ast & Divide_Ast::compile(){
	Code_For_Ast *cfa = new Code_For_Ast();
	
	Code_For_Ast *lhs_cfa = &(this->lhs)->compile();
	Code_For_Ast *rhs_cfa = &(this->rhs)->compile();

	list<Icode_Stmt *> lhs_ics_list = lhs_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = lhs_ics_list.begin(); it != lhs_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
	}

	list<Icode_Stmt *> rhs_ics_list = rhs_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = rhs_ics_list.begin(); it != rhs_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
	}
	
	Register_Addr_Opd *opd1 = new Register_Addr_Opd(lhs_cfa->get_reg());
	Register_Addr_Opd *opd2 = new Register_Addr_Opd(rhs_cfa->get_reg());

	Register_Descriptor * result_reg = new Register_Descriptor();
	Tgt_Op op;
	if(this->get_data_type() == int_data_type){
		result_reg = machine_desc_object.get_new_register<int_reg>();
		op = divd;
	}
	else if(this->get_data_type() == double_data_type){
		result_reg = machine_desc_object.get_new_register<float_reg>();
		op = div_d;
	}

	result_reg->set_use_for_expr_result();
	Register_Addr_Opd *result = new Register_Addr_Opd(result_reg);
	Compute_IC_Stmt *comp_ics = new Compute_IC_Stmt(op, opd1, opd2, result);
	cfa->append_ics(*comp_ics);
	lhs_cfa->get_reg()->reset_use_for_expr_result();
	rhs_cfa->get_reg()->reset_use_for_expr_result();
	cfa->set_reg(result_reg);
	return *cfa;
}
Code_For_Ast & Divide_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}


Code_For_Ast & Mult_Ast::compile(){
	Code_For_Ast *cfa = new Code_For_Ast();
	
	Code_For_Ast *lhs_cfa = &(this->lhs)->compile();
	Code_For_Ast *rhs_cfa = &(this->rhs)->compile();

	list<Icode_Stmt *> lhs_ics_list = lhs_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = lhs_ics_list.begin(); it != lhs_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
	}

	list<Icode_Stmt *> rhs_ics_list = rhs_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = rhs_ics_list.begin(); it != rhs_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
	}
	
	Register_Addr_Opd *opd1 = new Register_Addr_Opd(lhs_cfa->get_reg());
	Register_Addr_Opd *opd2 = new Register_Addr_Opd(rhs_cfa->get_reg());

	Register_Descriptor * result_reg = new Register_Descriptor();
	Tgt_Op op;
	if(this->get_data_type() == int_data_type){
		result_reg = machine_desc_object.get_new_register<int_reg>();
		op = mult;
	}
	else if(this->get_data_type() == double_data_type){
		result_reg = machine_desc_object.get_new_register<float_reg>();
		op = mult_d;
	}
	
	result_reg->set_use_for_expr_result();
	Register_Addr_Opd *result = new Register_Addr_Opd(result_reg);
	Compute_IC_Stmt *comp_ics = new Compute_IC_Stmt(op, opd1, opd2, result);
	cfa->append_ics(*comp_ics);
	lhs_cfa->get_reg()->reset_use_for_expr_result();
	rhs_cfa->get_reg()->reset_use_for_expr_result();
	cfa->set_reg(result_reg);
	return *cfa;
}
Code_For_Ast & Mult_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}


Code_For_Ast & UMinus_Ast::compile(){
	Code_For_Ast *cfa = new Code_For_Ast();
	
	Code_For_Ast *lhs_cfa = &(this->lhs)->compile();

	list<Icode_Stmt *> lhs_ics_list = lhs_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = lhs_ics_list.begin(); it != lhs_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
	}

	Register_Addr_Opd *opd1 = new Register_Addr_Opd(lhs_cfa->get_reg());

	Register_Descriptor * result_reg = new Register_Descriptor();
	Tgt_Op op;
	if(this->get_data_type() == int_data_type){
		result_reg = machine_desc_object.get_new_register<int_reg>();
		op = uminus;
	}
	else if(this->get_data_type() == double_data_type){
		result_reg = machine_desc_object.get_new_register<float_reg>();
		op = uminus_d;
	}

	result_reg->set_use_for_expr_result();
	Register_Addr_Opd *result = new Register_Addr_Opd(result_reg);
	Move_IC_Stmt *move_ics = new Move_IC_Stmt(op, opd1, result);
	cfa->append_ics(*move_ics);
	lhs_cfa->get_reg()->reset_use_for_expr_result();
	cfa->set_reg(result_reg);
	return *cfa;
}
Code_For_Ast & UMinus_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}


Code_For_Ast & Conditional_Expression_Ast::compile(){
	// printf("In Conditional_Expression_Ast compile\n");
	Code_For_Ast *cfa = new Code_For_Ast();
	
	Code_For_Ast *cond_cfa = &(this->cond)->compile();
	string label1 = get_new_label();
	Code_For_Ast *lhs_cfa = &(this->lhs)->compile();
	Code_For_Ast *rhs_cfa = &(this->rhs)->compile();
	string label2 = get_new_label();

	list<Icode_Stmt *> cond_ics_list = cond_cfa->get_icode_list();
	Tgt_Op opp;
	for (list<Icode_Stmt*>::iterator it = cond_ics_list.begin(); it != cond_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
		opp = ((*it)->get_op()).get_op();
	}

	if((this->cond)->get_data_type() == int_data_type){
		Register_Addr_Opd *cond_opd1 = new Register_Addr_Opd(cond_cfa->get_reg());
		Register_Descriptor *zero_reg = machine_desc_object.spim_register_table[zero];
		Register_Addr_Opd *cond_opd2 = new Register_Addr_Opd(zero_reg);
		Control_Flow_IC_Stmt *cf_ics = new Control_Flow_IC_Stmt(beq, cond_opd1, cond_opd2, label1);
		cfa->append_ics(*cf_ics);
	}
	else if((this->cond)->get_data_type() == double_data_type){
		if(opp == slt_d || opp == sle_d || opp == seq_d){
			Label_IC_Stmt *label_ics = new Label_IC_Stmt(bc1f, label1);
			cfa->append_ics(*label_ics);
		}
		else if(opp == sgt_d || opp == sge_d || opp == sne_d){
			Label_IC_Stmt *label_ics = new Label_IC_Stmt(bc1t, label1);
			cfa->append_ics(*label_ics);	
		}
	}

	list<Icode_Stmt *> lhs_ics_list = lhs_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = lhs_ics_list.begin(); it != lhs_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
	}

	Register_Descriptor *opd2_reg = machine_desc_object.spim_register_table[zero];
	Register_Addr_Opd *opd2 = new Register_Addr_Opd(opd2_reg);
	Register_Descriptor *result_reg = new Register_Descriptor();

	if(this->get_data_type() == int_data_type){
		result_reg = machine_desc_object.get_new_register<int_reg>();	
	}
	else if(this->get_data_type() == double_data_type){
		result_reg = machine_desc_object.get_new_register<float_reg>();
	}
	// Register_Descriptor *result_reg = machine_desc_object.get_new_register<int_reg>();
	Register_Addr_Opd *result = new Register_Addr_Opd(result_reg);
	
	Register_Addr_Opd *lhs_opd1 = new Register_Addr_Opd(lhs_cfa->get_reg());
	Compute_IC_Stmt *lhs_comp_ics = new Compute_IC_Stmt(or_t, lhs_opd1, opd2, result);
	cfa->append_ics(*lhs_comp_ics);

	Label_IC_Stmt *label_ics = new Label_IC_Stmt(j, label2);
	cfa->append_ics(*label_ics);

	Label_IC_Stmt *label_ics1 = new Label_IC_Stmt(label, label1);
	cfa->append_ics(*label_ics1);

	list<Icode_Stmt *> rhs_ics_list = rhs_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = rhs_ics_list.begin(); it != rhs_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
	}

	Register_Addr_Opd *rhs_opd1 = new Register_Addr_Opd(rhs_cfa->get_reg());
	Compute_IC_Stmt *rhs_comp_ics = new Compute_IC_Stmt(or_t, rhs_opd1, opd2, result);
	cfa->append_ics(*rhs_comp_ics);
	
	Label_IC_Stmt *label_ics2 = new Label_IC_Stmt(label, label2);
	cfa->append_ics(*label_ics2);

	// cond_cfa->get_reg()->reset_use_for_expr_result();
	if((this->cond)->get_data_type() == int_data_type){
		cond_cfa->get_reg()->reset_use_for_expr_result();
	}
	lhs_cfa->get_reg()->reset_use_for_expr_result();
	rhs_cfa->get_reg()->reset_use_for_expr_result();
	cfa->set_reg(result_reg);
	// printf("Out Conditional_Expression_Ast compile\n");
	return *cfa;
}


Code_For_Ast & Relational_Expr_Ast::compile(){
	// printf("In Relational_Expr_Ast compile\n");
	Code_For_Ast *cfa = new Code_For_Ast();
	
	Code_For_Ast *lhs_cfa = &(this->lhs_condition)->compile();
	Code_For_Ast *rhs_cfa = &(this->rhs_condition)->compile();

	list<Icode_Stmt *> lhs_ics_list = lhs_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = lhs_ics_list.begin(); it != lhs_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
	}

	list<Icode_Stmt *> rhs_ics_list = rhs_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = rhs_ics_list.begin(); it != rhs_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
	}
	
	Register_Addr_Opd *opd1 = new Register_Addr_Opd(lhs_cfa->get_reg());
	Register_Addr_Opd *opd2 = new Register_Addr_Opd(rhs_cfa->get_reg());
	
	if(this->get_data_type() == int_data_type){
		Register_Descriptor * result_reg = machine_desc_object.get_new_register<int_reg>();
		result_reg->set_use_for_expr_result();
		Register_Addr_Opd *result = new Register_Addr_Opd(result_reg);

		Tgt_Op op;
		if(this->rel_op == less_equalto){
			op = sle;
		}
		else if(this->rel_op == less_than){
			op = slt;
		}
		else if(this->rel_op == greater_than){
			op = sgt;
		}
		else if(this->rel_op == greater_equalto){
			op = sge;
		}
		else if(this->rel_op == equalto){
			op = seq;
		}
		else if(this->rel_op == not_equalto){
			op = sne;
		}

		Compute_IC_Stmt *comp_ics = new Compute_IC_Stmt(op, opd1, opd2, result);
		cfa->append_ics(*comp_ics);
		cfa->set_reg(result_reg);
	}
	else if(this->get_data_type() == double_data_type){
		Register_Descriptor * result_reg = machine_desc_object.get_new_register<int_reg>();
		result_reg->set_use_for_expr_result();
		Register_Addr_Opd *result = new Register_Addr_Opd(result_reg);

		Tgt_Op op;
		if(this->rel_op == less_equalto){
			op = sle_d;
		}
		else if(this->rel_op == less_than){
			op = slt_d;
		}
		else if(this->rel_op == greater_than){
			op = sgt_d;
		}
		else if(this->rel_op == greater_equalto){
			op = sge_d;
		}
		else if(this->rel_op == equalto){
			op = seq_d;
		}
		else if(this->rel_op == not_equalto){
			op = sne_d;
		}

		Compute_IC_Stmt *comp_ics = new Compute_IC_Stmt(op, opd1, opd2, result);
		cfa->append_ics(*comp_ics);
	}


	lhs_cfa->get_reg()->reset_use_for_expr_result();
	rhs_cfa->get_reg()->reset_use_for_expr_result();
	// result_reg->reset_use_for_expr_result();
	// printf("Out Relational_Expr_Ast compile\n");
	return *cfa;
}


Code_For_Ast & Logical_Expr_Ast::compile(){
	// printf("In Logical_Expr_Ast compile\n");
	if((this->rhs_op)->get_data_type() == double_data_type){
		char err[100];
		sprintf(err, "cs316: Error: Line: %d: Floating Point Boolean Operation is too hard!!!", this->lineno); 
		yyerror(err);
		exit(-1);
	}
	if(this->lhs_op != NULL){
		if((this->lhs_op)->get_data_type() == double_data_type){
			char err[100];
			sprintf(err, "cs316: Error: Line: %d: Floating Point Boolean Operation is too hard!!!", this->lineno); 
			yyerror(err);
			exit(-1);
		}
	}
	Code_For_Ast *cfa = new Code_For_Ast();

	Code_For_Ast *rhs_cfa = new Code_For_Ast();

	Register_Descriptor *lhs_reg = new Register_Descriptor();
	Register_Descriptor *rhs_reg = new Register_Descriptor();
	Tgt_Op op;
	if(this->bool_op == _logical_not){
		rhs_reg = machine_desc_object.get_new_register<int_reg>();
		Const_Opd<int> *rhs_opd1 = new Const_Opd<int>(1);
		Register_Addr_Opd *rhs_result = new Register_Addr_Opd(rhs_reg);
		Move_IC_Stmt *move_ics = new Move_IC_Stmt(imm_load, rhs_opd1, rhs_result);
		cfa->append_ics(*move_ics);
		Code_For_Ast *lhs_cfa = &(this->rhs_op)->compile();
		list<Icode_Stmt *> lhs_ics_list = lhs_cfa->get_icode_list();
		for (list<Icode_Stmt*>::iterator it = lhs_ics_list.begin(); it != lhs_ics_list.end(); ++it){
			cfa->append_ics(*(*it));
		}
		lhs_reg = lhs_cfa->get_reg();
		op = not_t;
	}
	else{
		Code_For_Ast *lhs_cfa = &(this->lhs_op)->compile();
		Code_For_Ast *rhs_cfa = &(this->rhs_op)->compile();
		
		list<Icode_Stmt *> lhs_ics_list = lhs_cfa->get_icode_list();
		for (list<Icode_Stmt*>::iterator it = lhs_ics_list.begin(); it != lhs_ics_list.end(); ++it){
			cfa->append_ics(*(*it));
		}
		
		list<Icode_Stmt *> rhs_ics_list = rhs_cfa->get_icode_list();
		for (list<Icode_Stmt*>::iterator it = rhs_ics_list.begin(); it != rhs_ics_list.end(); ++it){
			cfa->append_ics(*(*it));
		}
		
		if(this->bool_op == _logical_or){
			op = or_t;
		}
		else if(this->bool_op == _logical_and){
			op = and_t;
		}
		lhs_reg = lhs_cfa->get_reg();
		rhs_reg = rhs_cfa->get_reg();
	}

	Register_Addr_Opd *opd1 = new Register_Addr_Opd(lhs_reg);
	Register_Addr_Opd *opd2 = new Register_Addr_Opd(rhs_reg);
	
	Register_Descriptor * result_reg = machine_desc_object.get_new_register<int_reg>();
	result_reg->set_use_for_expr_result();
	Register_Addr_Opd *result = new Register_Addr_Opd(result_reg);
	cfa->set_reg(result_reg);

	Compute_IC_Stmt *comp_ics = new Compute_IC_Stmt(op, opd1, opd2, result);
	cfa->append_ics(*comp_ics);

	lhs_reg->reset_use_for_expr_result();
	rhs_reg->reset_use_for_expr_result();
	
	// printf("Out Logical_Expr_Ast compile\n");
	return *cfa;
}


Code_For_Ast & Selection_Statement_Ast::compile(){
	// printf("In Selection_Statement_Ast compile\n");
	Code_For_Ast *cfa = new Code_For_Ast();
	
	Code_For_Ast *cond_cfa = &(this->cond)->compile();

	Tgt_Op opp;
	list<Icode_Stmt *> cond_ics_list = cond_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = cond_ics_list.begin(); it != cond_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
		opp = ((*it)->get_op()).get_op();
	}
	
	Code_For_Ast *then_cfa = &(this->then_part)->compile();
	
	string label1 = get_new_label();
	if((this->cond)->get_data_type() == int_data_type){
		Register_Addr_Opd *cond_opd1 = new Register_Addr_Opd(cond_cfa->get_reg());
		Register_Descriptor *zero_reg = machine_desc_object.spim_register_table[zero];
		Register_Addr_Opd *cond_opd2 = new Register_Addr_Opd(zero_reg);
		Control_Flow_IC_Stmt *cf_ics = new Control_Flow_IC_Stmt(beq, cond_opd1, cond_opd2, label1);
		cfa->append_ics(*cf_ics);
	}
	else if((this->cond)->get_data_type() == double_data_type){
		if(opp == slt_d || opp == sle_d || opp == seq_d){
			Label_IC_Stmt *label_ics = new Label_IC_Stmt(bc1f, label1);
			cfa->append_ics(*label_ics);
		}
		else if(opp == sgt_d || opp == sge_d || opp == sne_d){
			Label_IC_Stmt *label_ics = new Label_IC_Stmt(bc1t, label1);
			cfa->append_ics(*label_ics);	
		}
	}
	
	list<Icode_Stmt *> then_ics_list = then_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = then_ics_list.begin(); it != then_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
	}

	if(this->else_part == NULL){
		Label_IC_Stmt *label_ics1 = new Label_IC_Stmt(label, label1);
		cfa->append_ics(*label_ics1);
	}
	else{
		string label2 = get_new_label();
		Code_For_Ast *else_cfa = &(this->else_part)->compile();
		Label_IC_Stmt *label_ics = new Label_IC_Stmt(j, label2);
		cfa->append_ics(*label_ics);

		Label_IC_Stmt *label_ics1 = new Label_IC_Stmt(label, label1);
		cfa->append_ics(*label_ics1);

		list<Icode_Stmt *> else_ics_list = else_cfa->get_icode_list();
		for (list<Icode_Stmt*>::iterator it = else_ics_list.begin(); it != else_ics_list.end(); ++it){
			cfa->append_ics(*(*it));
		}
		
		Label_IC_Stmt *label_ics2 = new Label_IC_Stmt(label, label2);
		cfa->append_ics(*label_ics2);
	}
	if((this->cond)->get_data_type() == int_data_type){
		cond_cfa->get_reg()->reset_use_for_expr_result();
	}

	// printf("Out Selection_Statement_Ast compile\n");
	return *cfa;
}


Code_For_Ast & Iteration_Statement_Ast::compile(){
	// printf("In Iteration_Statement_Ast compile\n");
	Code_For_Ast *cfa = new Code_For_Ast();
	
	Code_For_Ast *cond_cfa = &(this->cond)->compile();

	string label1 = get_new_label();
	string label2 = get_new_label();
	
	Code_For_Ast *body_cfa = &(this->body)->compile();

	if(!(this->is_do_form)){
		Label_IC_Stmt *label_ics = new Label_IC_Stmt(j, label2);
		cfa->append_ics(*label_ics);
	}

	Label_IC_Stmt *label_ics1 = new Label_IC_Stmt(label, label1);
	cfa->append_ics(*label_ics1);

	list<Icode_Stmt *> body_ics_list = body_cfa->get_icode_list();
	for (list<Icode_Stmt*>::iterator it = body_ics_list.begin(); it != body_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
	}

	Label_IC_Stmt *label_ics2 = new Label_IC_Stmt(label, label2);
	cfa->append_ics(*label_ics2);
	
	list<Icode_Stmt *> cond_ics_list = cond_cfa->get_icode_list();
	Tgt_Op opp;
	for (list<Icode_Stmt*>::iterator it = cond_ics_list.begin(); it != cond_ics_list.end(); ++it){
		cfa->append_ics(*(*it));
		opp = ((*it)->get_op()).get_op();
	}
	if((this->cond)->get_data_type() == int_data_type){
		Register_Addr_Opd *cond_opd1 = new Register_Addr_Opd(cond_cfa->get_reg());
		Register_Descriptor *zero_reg = machine_desc_object.spim_register_table[zero];
		Register_Addr_Opd *cond_opd2 = new Register_Addr_Opd(zero_reg);
		Control_Flow_IC_Stmt *cf_ics = new Control_Flow_IC_Stmt(bne, cond_opd1, cond_opd2, label1);
		cfa->append_ics(*cf_ics);
		cond_cfa->get_reg()->reset_use_for_expr_result();
	}
	else if((this->cond)->get_data_type() == double_data_type){
		// printf("Here111111111111111\n");
		if(opp == slt_d || opp == sle_d || opp == seq_d){
			Label_IC_Stmt *label_ics = new Label_IC_Stmt(bc1t, label1);
			cfa->append_ics(*label_ics);
		}
		else if(opp == sgt_d || opp == sge_d || opp == sne_d){
			Label_IC_Stmt *label_ics = new Label_IC_Stmt(bc1f, label1);
			cfa->append_ics(*label_ics);	
		}
	}

	// printf("Out Iteration_Statement_Ast compile\n");
	return *cfa;
}


Code_For_Ast & Sequence_Ast::compile(){
	// printf("In Sequence_Ast compile\n");
	Code_For_Ast *cfa = new Code_For_Ast();
	for (list<Ast*>::iterator it1 = (this->statement_list).begin(); it1 != (this->statement_list).end(); ++it1){
		Code_For_Ast *itr_cfa = &(*it1)->compile();
		list<Icode_Stmt*> ics_list = itr_cfa->get_icode_list();
		for (list<Icode_Stmt*>::iterator it2 = ics_list.begin(); it2 != ics_list.end(); ++it2){
			cfa->append_ics(*(*it2));
			(this->sa_icode_list).push_back((*it2));
		}
	}
	// printf("Out Sequence_Ast compile\n");
	return *cfa;
}
void Sequence_Ast::print_icode(ostream &file_buffer){
	printf("Sequence_Ast print_icode\n");
}
void Sequence_Ast::print_assembly(ostream &file_buffer){
	printf("Sequence_Ast print_assembly\n");

}


Code_For_Ast & Print_Ast::compile(){
	Code_For_Ast *cfa = new Code_For_Ast();

	Register_Descriptor * load_reg = new Register_Descriptor();
	int syscall_no;
	Tgt_Op op;
	if((this->var)->get_data_type() == int_data_type){
		syscall_no = 1;
		load_reg = machine_desc_object.spim_register_table[a0];
		op = load;
	}
	else if((this->var)->get_data_type() == double_data_type){
		syscall_no = 3;
		load_reg = machine_desc_object.spim_register_table[f12];
		op = load_d;
	}

	Const_Opd<int> *opd1 = new Const_Opd<int>(syscall_no);
	Register_Descriptor *result_reg = machine_desc_object.spim_register_table[v0];
	Register_Addr_Opd *result = new Register_Addr_Opd(result_reg);
	Move_IC_Stmt *move_ics = new Move_IC_Stmt(imm_load, opd1, result);
	cfa->append_ics(*move_ics);
	// result_reg->reset_use_for_expr_result();
	
	Symbol_Table_Entry *se = &((this->var)->get_symbol_entry());
	Mem_Addr_Opd *load_opd1 = new Mem_Addr_Opd(*se);
	Register_Addr_Opd *load_result = new Register_Addr_Opd(load_reg);
	Move_IC_Stmt *load_move_ics = new Move_IC_Stmt(op, load_opd1, load_result);
	cfa->append_ics(*load_move_ics);
	// load_reg->reset_use_for_expr_result();
	Print_IC_Stmt *prnt_ics = new Print_IC_Stmt();
	cfa->append_ics(*prnt_ics);
	return *cfa;
}


Code_For_Ast & Call_Ast::compile(){
	// printf("In Call_Ast compile\n");
	// cout<<"Called Procedure : "<<this->procedure_name<<endl;
	Code_For_Ast *cfa = new Code_For_Ast();
	Procedure *procedure = program_object.get_procedure_prototype(this->procedure_name);
	
	Symbol_Table formal_table = procedure->get_formal_param_list();
	list<Symbol_Table_Entry*> formal_param_list = formal_table.get_table();
	list<Symbol_Table_Entry*>::iterator it2 = formal_param_list.end();
	
	int offset = 0;

	list<Ast*> act_param_list = this->actual_param_list;
	act_param_list.reverse();
	for (list<Ast*>::iterator it = act_param_list.begin(); it != act_param_list.end(); ++it){
		Ast *ast = *it;
		Code_For_Ast *ast_cfa = &(ast->compile());
		list<Icode_Stmt *> ast_ics_list = ast_cfa->get_icode_list();
		for (list<Icode_Stmt*>::iterator it1 = ast_ics_list.begin(); it1 != ast_ics_list.end(); ++it1){
			cfa->append_ics(*(*it1));
		}
		Register_Addr_Opd *opd1 = new Register_Addr_Opd(ast_cfa->get_reg());
		
		it2--;
		Symbol_Table_Entry *var = *it2;
		string name = var->get_variable_name();
		Data_Type type = var->get_data_type();
		Symbol_Table_Entry *param = new Symbol_Table_Entry(name, type, this->lineno, sp_ref);
		param->set_symbol_scope(formal);
		param->set_start_offset(-offset);
		Mem_Addr_Opd *result = new Mem_Addr_Opd(*param);
		Tgt_Op op;
		if(type == int_data_type){
			offset += 4;
			op = store;
		}
		else if(type == double_data_type){
			offset += 8;
			op = store_d;
		}
		Move_IC_Stmt *move_ics = new Move_IC_Stmt(op, opd1, result);
		cfa->append_ics(*move_ics);
		ast_cfa->get_reg()->reset_use_for_expr_result();
	}
	if(formal_table.is_empty()){
		Label_IC_Stmt *label_ics = new Label_IC_Stmt(jal, this->procedure_name);
		cfa->append_ics(*label_ics);
	}
	else{
		Register_Descriptor *sp_reg = machine_desc_object.spim_register_table[sp];
		Register_Addr_Opd *opd1 = new Register_Addr_Opd(sp_reg);
		// printf("start_offset = %d, table_size = %d\n", start_offset, table_size);
		Const_Opd<int> *opd2 = new Const_Opd<int>(offset);
		Register_Addr_Opd *result = new Register_Addr_Opd(sp_reg);
		Compute_IC_Stmt *comp_ics = new Compute_IC_Stmt(sub, opd1, opd2, result);
		cfa->append_ics(*comp_ics);

		Label_IC_Stmt *label_ics = new Label_IC_Stmt(jal, this->procedure_name);
		cfa->append_ics(*label_ics);

		Compute_IC_Stmt *comp_ics1 = new Compute_IC_Stmt(add, opd1, opd2, result);
		cfa->append_ics(*comp_ics1);

	}

	Tgt_Op op;
	if(this->get_data_type() != void_data_type){
		// printf("Here11111\n");
		Register_Descriptor *result_reg = new Register_Descriptor();
		Register_Descriptor *ret_reg = new Register_Descriptor();
		if(this->get_data_type() == int_data_type){
			result_reg = machine_desc_object.get_new_register<int_reg>();
			ret_reg = machine_desc_object.spim_register_table[v1];
			op = mov;
		}
		else if(this->get_data_type() == double_data_type){
			result_reg = machine_desc_object.get_new_register<float_reg>();
			ret_reg = machine_desc_object.spim_register_table[f0];
			op = move_d;
		}
		if(this->return_value_reg == NULL){
			result_reg->reset_use_for_expr_result();
		}
		Register_Addr_Opd *opd = new Register_Addr_Opd(ret_reg);
		Register_Addr_Opd *result1 = new Register_Addr_Opd(result_reg);
		Move_IC_Stmt *move_ics = new Move_IC_Stmt(op, opd, result1);
		cfa->append_ics(*move_ics);
		cfa->set_reg(result_reg);
	}
	// printf("Out Call_Ast compile\n");
	return *cfa;
}
Code_For_Ast & Call_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}


Code_For_Ast & Return_Ast::compile(){
	// printf("In Return_Ast compile\n");
	Code_For_Ast *cfa = new Code_For_Ast();
	if(this->return_value != NULL){
		Code_For_Ast *retr_cfa = &(this->return_value)->compile();
		list<Icode_Stmt *> retr_ics_list = retr_cfa->get_icode_list();
		for (list<Icode_Stmt*>::iterator it = retr_ics_list.begin(); it != retr_ics_list.end(); ++it){
			cfa->append_ics(*(*it));
		}
		Register_Addr_Opd *opd1 = new Register_Addr_Opd(retr_cfa->get_reg());
		Register_Descriptor *result_reg = new Register_Descriptor();
		Tgt_Op op;
		if(this->get_data_type() == int_data_type){
			result_reg = machine_desc_object.spim_register_table[v1];
			op = mov;
		}
		else if(this->get_data_type() == double_data_type){
			result_reg = machine_desc_object.spim_register_table[f0];
			op = move_d;
		}
		Register_Addr_Opd *result = new Register_Addr_Opd(result_reg);
		Move_IC_Stmt *move_ics = new Move_IC_Stmt(op, opd1, result);
		cfa->append_ics(*move_ics);
		retr_cfa->get_reg()->reset_use_for_expr_result();
		cfa->set_reg(result_reg);
	}
	string epilog = "epilogue_" + this->proc_name;
	Label_IC_Stmt *retr_ics = new Label_IC_Stmt(ret_inst, epilog);
	cfa->append_ics(*retr_ics);
	// printf("Out Return_Ast compile\n");
	return *cfa;
}
Code_For_Ast & Return_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}