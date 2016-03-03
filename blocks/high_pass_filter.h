struct high_pass_filter_options_int {
  int factor;
};

struct high_pass_filter_options_afp {
  int factor;
};

struct high_pass_filter_options_float {
  float factor;
};

int64_t high_pass_filter_acc_int = 0;
int64_t high_pass_filter_acc_afp = 0;
float high_pass_filter_acc_float = 0;

void high_pass_filter_int(struct high_pass_filter_options_int *options, int *in, int *out) {
	high_pass_filter_acc_int *= 0xF000;
	high_pass_filter_acc_int += ((int64_t)(*in) * 0x1000);
	high_pass_filter_acc_int = high_pass_filter_acc_int >> 32;
	*out = *in - (int)high_pass_filter_acc_int;
}

void high_pass_filter_afp(struct high_pass_filter_options_afp *options, int *in, int *out) {
	high_pass_filter_acc_afp *= 0xF000;
	high_pass_filter_acc_afp += ((int64_t)(*in) * 0x1000);
	high_pass_filter_acc_afp = high_pass_filter_acc_afp >> 32;
	*out = *in - (int)high_pass_filter_acc_afp;
}

void high_pass_filter_float(struct high_pass_filter_options_float *options, float *in, float *out) {
	high_pass_filter_acc_float *= 0.9375;
	high_pass_filter_acc_float += *in * 0.0625;
	*out = *in - high_pass_filter_acc_float;
}

