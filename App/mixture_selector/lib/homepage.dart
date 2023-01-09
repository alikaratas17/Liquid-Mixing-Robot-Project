import 'package:flutter/material.dart';
import 'package:mixture_selector/drink_widget.dart';

import 'order_drink.dart';
import 'liquid_dropdown.dart';
import 'ml_button.dart';

class MyApplication extends StatelessWidget {
  Widget build(BuildContext context) {
    return MaterialApp(title: "Mixture Selector", home: MyHomePage());
  }
}

class MyHomePage extends StatelessWidget {
  late List<String> list;
  late List<LiquidDropdownMenu> menus;
  late TextEditingController controller;
  double ml_amount = 200.0;
  var ml_button;
  MyHomePage() {
    list = ["Lemon Juice", "Orange Juice", "Grenadine Juice", "Apple Juice"];
    menus = [
      LiquidDropdownMenu(list, 0),
      LiquidDropdownMenu(list, 1),
      LiquidDropdownMenu(list, 2),
      LiquidDropdownMenu(list, 3)
    ];
    controller = TextEditingController();
    ml_button = Ml_Button();
  }
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(title: Text('Mixture Selection Homepage')),
        body: Column(
          children: [
            Container(alignment: Alignment.bottomLeft,child:Text("Select Drink Size:"),),
            Container(alignment: Alignment.center,child:ml_button),
            Container(
              alignment: Alignment.center,
              child: ElevatedButton(
                  onPressed: () {
                    Navigator.of(context).push(MaterialPageRoute(
                        builder: (context) => MyOrderScreen(menus.map((x) {
                              return x.my_state.dropdownValue;
                            }).toList(),ml_button.my_state.current_value * 1.0)));
                  },
                  child: const Text('Make Custom Mixture')),
            ),
            Container(
              alignment: Alignment.center,
              child: Column(children: menus),
            ),
            
            Container(
                alignment: Alignment.center,
                child: TextField(
                  controller: controller,
                  onSubmitted: (String value) {
                    list.add(value);
                    for (int i = 0; i < 4; i++) menus[i].my_state.setList(list);
                    controller.clear();
                  },
                  decoration: InputDecoration(
                    border: OutlineInputBorder(),
                    labelText: "Enter New Liquid",
                  ),
                  textAlign: TextAlign.center,
                )),
          ],
        ));
  }
}
