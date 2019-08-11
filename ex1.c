int i1, i2;
float f1, f2;

float g(float);
float h(float);

float g(float argg){
	float t1, t2;
	if (argg < 1.0){
		return 1.0 - 0.0;
	}
	t1 = g(argg - 1.0);
	t2 = h(argg - 1.0);
	return t1 + t2;
}
float h(float argg){
	float t1, t2;
	if (argg < 1.0){
		return 1.0 - 0.0;
	}
	t1 = g(argg - 1.0);
	t2 = h(argg - 1.0);
	return t1 + t2;
}

void main(){
	f1 = 5.0;
	f2 = 4.0;
	f1 = g(f1);
	print f1;
}