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
  List<Widget> images = List();

  TextEditingController writeToFileText = TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Acrylic2D"),
      ),
      body: ListView(
        children: <Widget>[
          Padding(
            padding: const EdgeInsets.all(8.0),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[
                SizedBox(
                  width: 300,
                  child: TextField(
                    controller: writeToFileText,
                    keyboardType: TextInputType.multiline,
                    maxLines: null,
                    decoration: InputDecoration(
                      hintText: "Hello World"
                    ),
                  ),
                ),
                Padding(
                  padding: const EdgeInsets.all(8.0),
                  child: RaisedButton(
                    child: Text("Write to file"),
                    onPressed: (){
                      showSavePanel((FileChooserResult result, List<String> paths){
                        if(result ==FileChooserResult.ok){
                          paths.forEach((String path){
                            print(path);
                            File(path).writeAsStringSync(writeToFileText.text);
                          });
                        }
                      },
                      allowedFileTypes: ['txt'],
                      suggestedFileName: "Acrylic2D-export",
                      confirmButtonText: "Export"
                      );
                    },
                  ),
                ),
              ],
            ),
          ),
          for(Widget image in images)
            image
        ],
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: (){
          showOpenPanel((FileChooserResult result, List<String> paths){
            if(result ==FileChooserResult.ok){
              setState((){
                paths.forEach((String path){
                  print(path);
                  images.add(Image.memory(File(path).readAsBytesSync()));
                });
              });
            }
          },
          allowsMultipleSelection: true,
          allowedFileTypes: ['png','jpg',"jpeg"]
          );
        },
        child: Icon(Icons.insert_drive_file),
      ),
    );
  }
}
