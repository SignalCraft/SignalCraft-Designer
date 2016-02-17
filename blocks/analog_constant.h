struct analog_constant_options {
	int16_t value;
};

void analog_constant (struct analog_constant_options *options, int16_t *out0) {
	*out0 = options->value;
}