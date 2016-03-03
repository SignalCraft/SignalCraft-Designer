struct saturation_options_int {
	int high_limit;
	int low_limit;
};

struct saturation_options_afp {
	int high_limit;
	int low_limit;
};

struct saturation_options_float {
	float high_limit;
	float low_limit;
};

void saturation_int(struct saturation_options_int *options, int *in0, int *out0) {
	if (*in0 > options->high_limit) {
		*out0 = options->high_limit;
	} else if (*in0 < options->low_limit) {
		*out0 = options->low_limit;
	} else {
		*out0 = *in0;
	}
}

void saturation_afp(struct saturation_options_afp *options, int *in0, int *out0) {
	if (*in0 > options->high_limit) {
		*out0 = options->high_limit;
	} else if (*in0 < options->low_limit) {
		*out0 = options->low_limit;
	} else {
		*out0 = *in0;
	}
}

void saturation_float(struct saturation_options_float *options, float *in0, float *out0) {
	if (*in0 > options->high_limit) {
		*out0 = options->high_limit;
	} else if (*in0 < options->low_limit) {
		*out0 = options->low_limit;
	} else {
		*out0 = *in0;
	}
}