import 'package:flutter/material.dart';

class Ml_Button extends StatefulWidget {
  late _Ml_ButtonState my_state;
  Ml_Button() {
    my_state = _Ml_ButtonState();
  }

  @override
  State<StatefulWidget> createState() {
    return my_state;
  }
}

class _Ml_ButtonState extends State<Ml_Button> {
  int? current_value = 200;

  @override
  Widget build(BuildContext context) {
    return Column(children: <Widget>[
      ListTile(
          title: const Text("100 ml"),
          leading: Radio<int>(
              value: 100,
              groupValue: current_value,
              onChanged: (value2) {
                setState(() {
                  current_value = value2;
                });
              })),
      ListTile(
          title: const Text("150 ml"),
          leading: Radio<int>(
              value: 150,
              groupValue: current_value,
              onChanged: (value2) {
                setState(() {
                  current_value = value2;
                });
              })),
      ListTile(
          title: const Text("200 ml"),
          leading: Radio<int>(
              value: 200,
              groupValue: current_value,
              onChanged: (value2) {
                setState(() {
                  current_value = value2;
                });
              }))
    ]);
  }
}
