import 'package:flutter/material.dart';
import 'package:mixture_selector/drink_widget.dart';

import 'order_drink.dart';
import 'liquid_dropdown.dart';

class MyApplication extends StatelessWidget {
  Widget build(BuildContext context) {
    return MaterialApp(title: "Mixture Selector", home: MyHomePage());
  }
}

class MyHomePage extends StatelessWidget {
  List<String> list = [
    "Lemon Juice",
    "Orange Juice",
    "Grenadine Juice",
    "Apple Juice"
  ];
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(title: Text('Mixture Selection Homepage')),
        body: Column(
          children: [
            Container(
              alignment: Alignment.center,
              child: ElevatedButton(
                  onPressed: () {
                    Navigator.of(context).push(MaterialPageRoute(
                        builder: (context) => MyOrderScreen()));
                  },
                  child: const Text('Make Custom Mixture')),
            ),
            Container(
              alignment: Alignment.center,
              child: Column(children: [
                LiquidDropdownMenu(list, 0),
                LiquidDropdownMenu(list, 1),
                LiquidDropdownMenu(list, 2),
                LiquidDropdownMenu(list, 3),
              ]),
            )
          ],
        ));
  }
}
