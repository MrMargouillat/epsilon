#ifndef APPS_INTERACTIVE_CURVE_VIEW_CONTROLLER_H
#define APPS_INTERACTIVE_CURVE_VIEW_CONTROLLER_H

#include <escher.h>
#include "interactive_curve_view_range.h"
#include "curve_view.h"
#include "cursor_view.h"
#include "banner_view.h"
#include "range_parameter_controller.h"
#include "zoom_parameter_controller.h"

class InteractiveCurveViewController : public ViewController, public HeaderViewDelegate, public AlternateEmptyViewDelegate {
public:
  InteractiveCurveViewController(Responder * parentResponder, HeaderViewController * header, InteractiveCurveViewRange * interactiveRange, CurveView * curveView);
  View * view() override;
  const char * title() const override;
  bool handleEvent(Ion::Events::Event event) override;
  void didBecomeFirstResponder() override;

  ViewController * rangeParameterController();
  ViewController * zoomParameterController();
  virtual ViewController * initialisationParameterController() = 0;

  int numberOfButtons() const override;
  Button * buttonAtIndex(int index) override;

  Responder * defaultController() override;
protected:
  virtual BannerView * bannerView() = 0;
  virtual bool handleEnter() = 0;
  Responder * tabController() const;
  StackViewController * stackController() const;
  virtual void reloadBannerView() = 0;
  virtual void initRangeParameters() = 0;
  virtual void initCursorParameters() = 0;
  /* the result of moveCursorVertically/Horizontally means:
   * -1 -> the cursor cannot move in this direction 
   * 0 -> the cursor moved but the window has not changed
   * 1-> the cursor moved and the window changed */
  virtual int moveCursorHorizontally(int direction) = 0;
  virtual int moveCursorVertically(int direction) = 0;
  virtual uint32_t modelVersion() = 0;
  virtual uint32_t rangeVersion() = 0;
  virtual InteractiveCurveViewRange * interactiveCurveViewRange() = 0;
  virtual CurveView * curveView() = 0;
  CurveViewCursor m_cursor;
  CursorView m_cursorView;
private:
  uint32_t m_modelVersion;
  uint32_t m_rangeVersion;
  RangeParameterController m_rangeParameterController;
  ZoomParameterController m_zoomParameterController;
  Button m_rangeButton;
  Button m_zoomButton;
  Button m_defaultInitialisationButton;
};

#endif