#!/bin/sh
INPUT_STRING=dentro
while [ "$RET" != "salir" ]
do
  echo "Please type something in (bye to quit)"
  read INPUT_STRING
  echo "You typed: $INPUT_STRING"
done