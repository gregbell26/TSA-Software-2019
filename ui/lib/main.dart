// Copyright 2018 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

import 'dart:io';

import 'package:flutter/foundation.dart'
    show debugDefaultTargetPlatformOverride;
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:acrylic_2d/colors.dart';
import 'package:file_chooser/file_chooser.dart';

void main() {
  // See https://github.com/flutter/flutter/wiki/Desktop-shells#target-platform-override
  debugDefaultTargetPlatformOverride = TargetPlatform.fuchsia;

  runApp(new MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Flutter Demo',
      theme: ThemeData(
        accentColor: AcrylicColors.accent,
        buttonColor: AcrylicColors.accent,
        primaryColor: AcrylicColors.accent,
        brightness: Brightness.dark,
        floatingActionButtonTheme: FloatingActionButtonThemeData(
          foregroundColor: Colors.white,
          backgroundColor: AcrylicColors.accent
        ),
        // See https://github.com/flutter/flutter/wiki/Desktop-shells#fonts
        fontFamily: 'Roboto',
      ),
      home: Main(),
    );
  }
}

class Main extends StatefulWidget {
  @override
  _MainState createState() => _MainState();
}

class _MainState extends State<Main> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Acrylic2D"),
      ),
      body: ListView(
        children: <Widget>[
          Row(
//            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: <Widget>[
              SizedBox(
                width: 450,
                child: Column(
                  children: <Widget>[
                    Text("Drag the things"),
                    Draggable<String>(
                      child: Container(
                        width: 30,
                        height: 30,
                        decoration: BoxDecoration(
                          color: Colors.red,
                          border: Border.all(
                            color: Colors.black,
                            width: 1.0,
                          ),
                        ),
                      ),
                      feedback: Container(
                          width: 30,
                          height: 30,
                        decoration: BoxDecoration(
                          color: Colors.red,
                          border: Border.all(
                            color: Colors.black,
                            width: 1.0,
                          ),
                        ),
                      ),
                      childWhenDragging: Container(
                        width: 30,
                        height: 30,
                        decoration: BoxDecoration(
                          color: Colors.green,
                          border: Border.all(
                            color: Colors.black,
                            width: 1.0,
                          ),
                        ),
                      ),
                      data: "testData"
                    )
                  ],
                )
              ),
              Column(
                children: <Widget>[
                  Text("Scene"),
                  SizedBox(
                    width: 300,
                    height: 300,
                    child: GridView.count(
                      crossAxisCount: 10,
                      // Generate 100 widgets that display their index in the List.
                      children: List.generate(100, (index) {
                        return UISquare(false);
                      }),
                    ),
                  )
                ],
              )
            ],
          )
        ],
      )
    );
  }
}

class UISquare extends StatefulWidget {
  final bool isActivated;
  UISquare(this.isActivated);
  @override
  _UISquareState createState() => _UISquareState();
}

class _UISquareState extends State<UISquare> {

  Color squareColor;
  Color savedColor;

  @override
  void initState() {
    super.initState();
    squareColor = widget.isActivated ? Colors.yellow : Colors.white;
  }

  void setActivated(Color newColor){
    setState((){
       squareColor = newColor;
    });
  }

  @override
  Widget build(BuildContext context) {
    return DragTarget<String>(
      onAccept: (String value){setActivated(Colors.yellow);},
      onWillAccept: (String value){savedColor = squareColor; setActivated(Colors.purple); return true;},
      onLeave: (String value){setActivated(Colors.white); squareColor = savedColor;},
      builder: (context,candidates,rejects){
        return Container(
          width: 30,
          height: 30,
          decoration: BoxDecoration(
            color: squareColor,
            border: Border.all(
              color: Colors.black,
              width: 1.0,
            ),
          ),
        );
      }
    );
  }
}
