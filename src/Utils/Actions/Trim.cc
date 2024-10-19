#include "Actions.h"

wstring trim(const wstring& str) {
  const auto start = str.find_first_not_of(L" \t\n\r");
  const auto end = str.find_last_not_of(L" \t\n\r");
  return (start == wstring::npos) ? L"" : str.substr(start, end - start + 1);
}
