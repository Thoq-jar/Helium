# Troubleshooting

### If you cant see the website/contents or the webview **appears** blank:
- Add this to your env variables:
```env
WEBKIT_DISABLE_COMPOSITING_MODE=1
```
in CLion

or run it like this:
```bash
WEBKIT_DISABLE_COMPOSITING_MODE=1 ./cmake-build-debug/Purr
```