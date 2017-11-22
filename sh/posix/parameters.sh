#!/usr/bin/env bash
#
# http://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_06_02

if [ -z "${file:-}" ]; then
  file="${BASH_SOURCE[0]}"
  file="${file}" sh "${file}"
  exit $?
fi

source "$(cd "$(dirname "${file}")" && pwd)/_.sh"

# Parameter Expansion

#                  set & not null   set & null    not set
# ${param:-word}   ${param}         word          word
# ${param-word}    ${param}         null          word
# ${param:=word}   ${param}         param=word    param=word
# ${param=word}    ${param}         null          param=word
# ${param:?word}   ${param}         error, exit   error, exit
# ${param?word}    ${param}         null          error, exit
# ${param:+word}   word             null          null
# ${param+word}    word             word          null

# Default Value: ${param:-word} or ${param-word}

example 'Default Value' '${param:-word} (!null)'
(x=a    ; [ "${x:-b}" = 'a' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Default Value' '${param:-word} (=null)'
(x=     ; [ "${x:-b}" = 'b' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Default Value' '${param:-word} (unset)'
(unset x; [ "${x:-b}" = 'b' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Default Value' '${param-word} (!null)'
(x=a    ; [ "${x-b}" = 'a' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Default Value' '${param-word} (=null)'
(x=     ; [ "${x-b}" = '' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Default Value' '${param-word} (unset)'
(unset x; [ "${x-b}" = 'b' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

# Assign Value: ${param:=word} or ${param=word}

example 'Assign Value' '${param:=word} (!null)'
(x=a    ; y="${x:=b}"; [ "$x" = 'a' -a "$y" = 'a' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Assign Value' '${param:=word} (=null)'
(x=     ; y="${x:=b}"; [ "$x" = 'b' -a "$y" = 'b' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Assign Value' '${param:=word} (unset)'
(unset x; y="${x:=b}"; [ "$x" = 'b' -a "$y" = 'b' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Assign Value' '${param=word} (!null)'
(x=a    ; y="${x=b}"; [ "$x" = 'a' -a "$y" = 'a' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Assign Value' '${param=word} (=null)'
(x=     ; y="${x=b}"; [ "$x" = '' -a "$y" = '' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Assign Value' '${param=word} (unset)'
(unset x; y="${x=b}"; [ "$x" = 'b' -a "$y" = 'b' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

# Error if Null/Unset: ${param:?word} or ${param?word}

example 'Error if Null/Unset' '${param:?word} (!null)'
(x=a    ; [ "${x:?b}" = 'a' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Error if Null/Unset' '${param:?word} (=null)'
(x=     ; [ "${x:?'parameter =null'}" = '' ] || exit 1)
[ "$?" -ne 0 ] && pass || fail

example 'Error if Null/Unset' '${param:?word} (unset)'
(unset x; [ "${x:?'parameter unset'}" = 'b' ] || exit 1)
[ "$?" -ne 0 ] && pass || fail

example 'Error if Null/Unset' '${param?word} (!null)'
(x=a    ; [ "${x?'parameter !null'}" = 'a' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Error if Null/Unset' '${param?word} (=null)'
(x=     ; [ "${x?'parameter =null'}" = '' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Error if Null/Unset' '${param?word} (unset)'
(unset x; [ "${x?'parameter unset'}" = 'b' ] || exit 1)
[ "$?" -ne 0 ] && pass || fail

# Alternate Value: ${param:+word} or ${param+word}

example 'Alternate Value' '${param:+word} (!null)'
(x=a    ; [ "${x:+b}" = 'b' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Alternate Value' '${param:+word} (=null)'
(x=     ; [ "${x:+b}" = '' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Alternate Value' '${param:+word} (unset)'
(unset x; [ "${x:+b}" = '' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Alternate Value' '${param+word} (!null)'
(x=a    ; [ "${x+b}" = 'b' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Alternate Value' '${param+word} (=null)'
(x=     ; [ "${x+b}" = 'b' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

example 'Alternate Value' '${param+word} (unset)'
(unset x; [ "${x+b}" = '' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

# Remove Smallest Suffix Pattern

example 'Remove Smallest Suffix Pattern' '${param%word}'
(x='a/b/c'; [ "${x%/*}" = 'a/b' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

# Remove Largest Suffix Pattern

example 'Remove Largest Suffix Pattern' '${param%%word}'
(x='a/b/c'; [ "${x%%/*}" = 'a' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

# Remove Smallest Prefix Pattern

example 'Remove Smallest Prefix Pattern' '${param%word}'
(x='a/b/c'; [ "${x#*/}" = 'b/c' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

# Remove Largest Prefix Pattern

example 'Remove Largest Prefix Pattern' '${param%word}'
(x='a/b/c'; [ "${x##*/}" = 'c' ] || exit 1)
[ "$?" -eq 0 ] && pass || fail

# String Length

example 'String Length' '${#x}'
(x='12345678'; [ ${#x} -eq 8 ] || exit 1)
[ "$?" -eq 0 ] && pass || fail
