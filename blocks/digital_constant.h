struct digital_constant_options {
	int value;
};

void digital_constant(struct digital_constant_options *options, int *out0) {
	*out0 = options->value;
}