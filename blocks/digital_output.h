struct digital_output_options {
	int *data;
};

void digital_output (struct digital_output_options *options, int *in0) {
	*(options->data) = *in0;
}