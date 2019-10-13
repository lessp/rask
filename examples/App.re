open Rask;

module Container = {
  [@react.component]
  let make = (~children as c) => {
    View.(
      make()
      ->backgroundColor(Hex("7cc0c0"))
      ->display(Flex)
      ->flexDirection(Column)
      ->justifyContent(Center)
      ->alignItems(Center)
      ->height(Vh(100))
      ->width(Vw(100))
      ->children(c)
      ->reactElement("div")
    );
  };
};

module HelloRask = {
  [@react.component]
  let make = () => {
    let (currentText, setText) = React.useState(() => "Hello");

    let toggleGreeting = _event =>
      setText(prevGreeting => prevGreeting == "Hello" ? "Rask!" : "Hello");

    <Components.Card>
      <Components.Title text=currentText onClick=toggleGreeting />
    </Components.Card>;
  };
};

[@react.component]
let make = () => <Container> <HelloRask /> </Container>;
