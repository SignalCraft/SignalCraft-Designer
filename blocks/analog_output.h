struct analog_output_options {
	int *data;
};

void analog_output (struct analog_output_options *options, int *in0) {
	*(options->data) = *in0;
}