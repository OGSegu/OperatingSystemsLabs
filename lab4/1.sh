#!/bin/bash
echo $var1
echo $var2

export var3=${var1}${var2}
echo $var3
export var3='not the save value'
echo $var3
