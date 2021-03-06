// Copyright (c) 2018 Slack Technologies, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef SHELL_BROWSER_FONT_DEFAULTS_H_
#define SHELL_BROWSER_FONT_DEFAULTS_H_

namespace content {
struct WebPreferences;
}  // namespace content

namespace electron {

void SetFontDefaults(content::WebPreferences* prefs);

}  // namespace electron

#endif  // SHELL_BROWSER_FONT_DEFAULTS_H_
