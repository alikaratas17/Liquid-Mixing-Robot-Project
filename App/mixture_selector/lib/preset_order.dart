import 'dart:ffi';

import 'package:flutter/material.dart';
import 'package:flutter/rendering.dart';
import 'my_key.dart' as my_key;
import 'package:http/http.dart' as http;
import 'drink_widget.dart';

class MyPresetOrderScreen extends StatefulWidget {
  late MyPresetOrderScreenState my_state;
  MyPresetOrderScreen(drinks, max_amount) {
    my_state = MyPresetOrderScreenState(drinks, max_amount);
  }
  @override
  State<StatefulWidget> createState() {
    return my_state;
  }
}

class MyPresetOrderScreenState extends State<MyPresetOrderScreen> {
  List<ElevatedButton> options = [];
  String message = "";
  List<String> all_options_names = ["Lemon-Orange","Grenadine-Orange","Apple-Pineapple"];
  List<List<String>> all_options_items = [["Lemon Juice","Orange Juice"],["Grenadine Juice","Orange Juice"],["Apple Juice","Pineapple Juice"]];

  MyPresetOrderScreenState(drinks, max_amount) {
    for (int i = 0; i < all_options_names.length; i++) {
      int len = all_options_items[i].length;
      int incl = 1;
      String mixture = '';
      for (int j = 0; j < len; j++) {
        if (!drinks.contains(all_options_items[i][j])) incl = 0;
      }
      int current = 0;
      if (incl == 1) {
      for (int j = 0; j < 4; j++) {
        if (!all_options_items[i].contains(drinks[j])){
        mixture = mixture + '0.0';
        }else{
        mixture = mixture + ((max_amount/len).round()*1.0).toString();
        }
        current ++;
        if (current !=len)mixture = mixture + ',';
      }
        options.add(ElevatedButton(
            child: Text(all_options_names[i]),
            onPressed: () => send_mixture(all_options_names[i], mixture)));
      }
    }
  }
  @override
  Widget build(BuildContext context) {
    Color getColor(Set<MaterialState> states) {
      const Set<MaterialState> interactiveStates = <MaterialState>{
        MaterialState.pressed,
        MaterialState.hovered,
        MaterialState.focused,
      };
      if (states.any(interactiveStates.contains)) {
        return Colors.blue;
      }
      return Colors.red;
    }

    //return //MaterialApp(title:"Select a Mixture",home:
    return Scaffold(
        appBar: AppBar(title: Text('Preset Mixture Selection')),
        body: Container(
          alignment: Alignment.center,
          child: Column(
            children: [
              Text(message),
              Column(
                children: this.options,
              )
            ],
          ),
        ));
  }

  void send_mixture(String name, String mixture) async {
    String my_url =
        'https://io.adafruit.com/api/v2/akaratas17/feeds/message/data?X-AIO-Key=' +
            my_key.key;
    final response =
        await http.post(Uri.parse(my_url), body: {'value': mixture});
    print(response.statusCode.toString()); // For debugging

    setState(() {
      message = "Order of " + name + " Received\n";
    });
  }
}
