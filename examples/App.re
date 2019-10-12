open Rask;

module Container = {
  [@react.component]
  let make = (~children as c) => {
    View.(
      make("div")
      ->backgroundColor(Hex("7cc0c0"))
      ->display(Flex)
      ->flexDirection(Column)
      ->justifyContent(Center)
      ->alignItems(Center)
      ->height(Vh(100))
      ->width(Vw(100))
      ->children(c)
      ->toReactElement
    );
  };
};

module HelloRask = {
  [@react.component]
  let make = () => {
    let (currentText, setText) = React.useState(() => "Hello");

    let clickMe =
      Text.(
        make("Click the text below!")
        ->fontSize(18)
        ->color(DarkGrey)
        ->toReactElement
      );

    let helloWorld =
      Text.(
        Theme.title(currentText)
        ->onClick(_event =>
            setText(prevGreeting =>
              prevGreeting == "Hello" ? "Rask!" : "Hello"
            )
          )
        ->toReactElement
      );

    View.(
      Theme.card
      ->children([|clickMe, helloWorld|]->React.array)
      ->toReactElement
    );
  };
};

[@react.component]
let make = () => <Container> <HelloRask /> </Container>;
