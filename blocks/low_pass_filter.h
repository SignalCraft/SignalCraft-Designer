struct low_pass_filter_options_int {
  int factor;
};

struct low_pass_filter_options_afp {
  int factor;
};

struct low_pass_filter_options_float {
  float factor;
};

int64_t low_pass_filter_acc_int = 0;
int64_t low_pass_filter_acc_afp = 0;
float low_pass_filter_acc_float = 0;

void low_pass_filter_int(struct low_pass_filter_options_int *options, int *in, int *out) {
	low_pass_filter_acc_int *= 0xF000;
	low_pass_filter_acc_int += ((int64_t)(*in) * 0x1000);
	low_pass_filter_acc_int = low_pass_filter_acc_int >> 32;
	*out = (int)low_pass_filter_acc_int;
}

void low_pass_filter_afp(struct low_pass_filter_options_afp *options, int *in, int *out) {
	low_pass_filter_acc_afp *= 0xF000;
	low_pass_filter_acc_afp += ((int64_t)(*in) * 0x1000);
	low_pass_filter_acc_afp = low_pass_filter_acc_afp >> 32;
	*out = (int)low_pass_filter_acc_afp;
}

void low_pass_filter_float(struct low_pass_filter_options_float *options, float *in, float *out) {
	low_pass_filter_acc_float *= 0.9375;
	low_pass_filter_acc_float += *in * 0.0625;
	*out = low_pass_filter_acc_float;
}

