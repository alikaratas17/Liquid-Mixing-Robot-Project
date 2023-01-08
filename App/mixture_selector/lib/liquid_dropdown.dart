import 'package:flutter/material.dart';

class LiquidDropdownMenu extends StatefulWidget {
  late _LiquidDropdownMenuState my_state;
  LiquidDropdownMenu(List<String> items, int i) {
    this.my_state = _LiquidDropdownMenuState(items, i);
  }

  @override
  State<StatefulWidget> createState() {
    return my_state;
  }
  // const LiquidDropdownMenu({super.key});

  // @override
  // State<LiquidDropdownMenu> createState() => _LiquidDropdownMenuState();
}

class _LiquidDropdownMenuState extends State<LiquidDropdownMenu> {
  late List<String> list;
  late String dropdownValue;
  late int i;
  _LiquidDropdownMenuState(List<String> items, int i) {
    this.list = items;
    this.dropdownValue = items[i];
    this.i = i + 1;
  }

  @override
  Widget build(BuildContext context) {
    return Container(
      child: Row(
        children: [
          SizedBox(width: 100),
          Text("Drink " + i.toString() + ":"),
          SizedBox(width: 40),
          DropdownButton<String>(
            value: dropdownValue,
            icon: const Icon(Icons.arrow_downward),
            elevation: 16,
            style: const TextStyle(color: Colors.blue),
            onChanged: (String? value) {
              // This is called when the user selects an item.
              setState(() {
                dropdownValue = value!;
              });
            },
            items: list.map<DropdownMenuItem<String>>((String value) {
              return DropdownMenuItem<String>(
                value: value,
                child: Text(value),
              );
            }).toList(),
          )
        ],
      ),
      alignment: Alignment.center,
    );
  }
}
