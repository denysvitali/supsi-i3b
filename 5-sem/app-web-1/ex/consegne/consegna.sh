#!/bin/bash
DIR_NAME=$1
tar --exclude='*.class' -cvf $DIR_NAME.tar.gz ../$DIR_NAME
