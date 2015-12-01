struct analog_input_options {
	int *data;
};

void analog_input (struct analog_input_options *options, int *out0) {
	*out0 = *(options->data);
}