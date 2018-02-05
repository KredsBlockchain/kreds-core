#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

KREDSD=${KREDSD:-$SRCDIR/kredsd}
KREDSCLI=${KREDSCLI:-$SRCDIR/kreds-cli}
KREDSTX=${KREDSTX:-$SRCDIR/kreds-tx}
KREDSQT=${KREDSQT:-$SRCDIR/qt/kreds-qt}

[ ! -x $KREDSD ] && echo "$KREDSD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
BSDVER=($($KREDSCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for kredsd if --version-string is not set,
# but has different outcomes for kreds-qt and kreds-cli.
echo "[COPYRIGHT]" > footer.h2m
$KREDSD --version | sed -n '1!p' >> footer.h2m

for cmd in $KREDSD $KREDSCLI $KREDSTX $KREDSQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${BSDVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${BSDVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
