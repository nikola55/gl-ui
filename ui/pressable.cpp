#include "pressable.h"

ui::Pressable::~Pressable() { }

void ui::Pressable::onPressHandler(ui::Pressable::OnPressHandler *) { }

ui::Pressable::OnPressHandler *ui::Pressable::onPressHandler() { return 0; }
