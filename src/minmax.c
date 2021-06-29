#include <vaccel.h>
#include <math.h>

#include "minmax.h"

int serrano_minmax(
	struct vaccel_session *sess,
	const double *indata, int ndata,
	int low_threshold, int high_threshold,
	double *outdata,
	double *min,
	double *max
) {
	if (!sess)
		return VACCEL_EINVAL;

	double tmp_max = -1.0;
	double tmp_min = 10000.0;

	for (int i = 0; i < ndata; ++i) {
		tmp_max = fmax(tmp_max, indata[i]);
		tmp_min = fmin(tmp_min, indata[i]);
	}

	for (int i = 0; i < ndata; i++)
		outdata[i] = ((indata[i] - tmp_min)
			/ (tmp_max - tmp_min))
			* (high_threshold - low_threshold)
			+ low_threshold;
	
	*min = tmp_min;
	*max = tmp_max;

	return VACCEL_OK;
}
