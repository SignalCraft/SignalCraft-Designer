struct saturation_options {
	int high_limit;
	int low_limit;
};

void saturation(struct saturation_options *options, int *in0, int *out0) {
	if (*in0 > options->high_limit) {
		*out0 = options->high_limit;
	} else if (*in0 < options->low_limit) {
		*out0 = options->low_limit;
	} else {
		*out0 = *in0;
	}
}