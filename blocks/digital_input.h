struct digital_input_options {
	int *data;
};

void digital_input(struct digital_input_options *options, int *out0) {
	*out0 = *(options->data);
}