import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter/foundation.dart'
    show debugDefaultTargetPlatformOverride;
import 'package:flutter/services.dart';
import 'package:acrylic_2d/colors.dart';
import 'package:file_chooser/file_chooser.dart';

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