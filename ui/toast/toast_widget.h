// This file is part of Desktop App Toolkit,
// a set of libraries for developing nice desktop applications.
//
// For license and copyright information please follow this link:
// https://github.com/desktop-app/legal/blob/master/LEGAL
//
#pragma once

#include "ui/toast/toast.h"
#include "ui/text/text.h"
#include "ui/rp_widget.h"
#include "ui/round_rect.h"

namespace Ui::Toast::internal {

class Widget final : public RpWidget {
public:
	Widget(QWidget *parent, Config &&config);

	// shownLevel=1 completely visible, shownLevel=0 completely invisible
	void setShownLevel(float64 shownLevel);

	void parentResized();

private:
	void paintEvent(QPaintEvent *e) override;

	void updateGeometry();
	void paintToProxy();
	void disableChildrenPaintOnce();
	void toggleChildrenPaint(bool enable);
	void scheduleChildrenPaintRestore();

	const not_null<const style::Toast*> _st;
	RoundRect _roundRect;
	RectPart _attach = RectPart::None;

	float64 _shownLevel = 0;
	QImage _shownProxy;

	object_ptr<RpWidget> _content;
	rpl::variable<QMargins> _padding;
	Fn<void(float64)> _updateShownGeometry;

	bool _childrenPaintDisabled : 1 = false;
	bool _childrenPaintRestoreScheduled : 1 = false;
	bool _adaptive : 1 = false;

};

} // namespace Ui::Toast::internal
