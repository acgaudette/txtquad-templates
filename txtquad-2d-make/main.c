#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "txtquad/txtquad.h"
#include "txtquad/inp.h"
void inp_ev_text(unsigned int unicode) {}

#include "acg/sys.h"

#define FIXED_DT (1.f / 120.f)
#include "acg/time.h"
struct _time _time;

#define MAX_DEPTH 8.f
#include "acg/cam.h"
static cam2 cam = CAM2_DEFAULT;

#define BG_COL ((v3) { .05f, .0f, .2f })
#include "impl.h"

struct txt_share txtquad_update(struct txt_frame frame, struct txt_buf *txt)
{
	txt->count = 0;
	_time.scale = 1.f;

	if (_time_tick(&frame.t, &frame.dt)) {
		/* ... */
	}

	while (_time_step()) {
		// ...
	}

	update();    // impl.h
	render(txt); // impl.h

	cam.asp = frame.size.w / (float)frame.size.h;
	return (struct txt_share) {
		.vp = cam2_conv(cam),
	};
}

int main()
{
	dump_vmem();
	srand(time(0));

	init();

	int key_handles[] = {
		  KEY(SPACE)
		, KEY(LEFT_SHIFT)
		, KEY(LEFT_CONTROL)
		, KEY(TAB)
		, KEY(ENTER)
		, KEY(BACKSPACE)
		, KEY(GRAVE_ACCENT)
		, KEY(LEFT)
		, KEY(RIGHT)
		, KEY(UP)
		, KEY(DOWN)
		, KEY(H)
		, KEY(J)
		, KEY(K)
		, KEY(L)
		, KEY(W)
		, KEY(A)
		, KEY(S)
		, KEY(D)
		, KEY(R)
		, KEY(Q)
		, KEY(E)
		, KEY(Z)
	};

	inp_key_init(key_handles, sizeof(key_handles) / sizeof(int));

	txtquad_init((struct txt_cfg) {
		.app_name = "jamxx",
		.asset_path = "./assets/",
		.mode = MODE_BORDERLESS,
		.clear_col = BG_COL,
	});

	txtquad_start();
}
