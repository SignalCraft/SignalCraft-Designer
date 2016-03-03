struct analog_constant_options {
	int value;
};

void analog_constant (struct analog_constant_options *options, int *out0) {
	*out0 = options->value << 27;
}