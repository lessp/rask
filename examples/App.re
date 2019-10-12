open Haste;

module Container = {
  [@react.component]
  let make = (~children as c) => {
    View.(
      make("div")
      ->backgroundColor(Color.Hex("#eaecec"))
      ->display(Display.Flex)
      ->flexDirection(Flex.FlexDirection.Column)
      ->justifyContent(Flex.JustifyContent.Center)
      ->alignItems(Flex.AlignItems.Center)
      ->height(Size.Vh(100))
      ->width(Size.Vw(100))
      ->children(c)
      ->toReactElement
    );
  };
};

module Hello = {
  [@react.component]
  let make = () => {
    let (currentText, setText) = React.useState(() => "Hello!");

    let toggleGreeting = _ =>
      setText(
        fun
        | "Hello!" => "World!"
        | _ => "Hello!",
      );

    let clickMe =
      Text.(make("Click the text below!")->fontSize(18)->toReactElement);

    let helloWorld =
      Text.(
        make(currentText)
        ->fontFamily("sans-serif")
        ->fontSize(32)
        ->color(Color.Pink)
        ->onClick(toggleGreeting)
        ->toReactElement
      );

    View.(
      make("div")
      ->backgroundColor(Color.White)
      ->display(Display.Flex)
      ->alignItems(Flex.AlignItems.Center)
      ->flexDirection(Flex.FlexDirection.Column)
      ->justifyContent(Flex.JustifyContent.SpaceEvenly)
      ->height(Size.Px(320))
      ->width(Size.Px(320))
      ->padding(~x=Size.Px(32), ~y=Size.Px(32))
      ->shadow(
          ~x=0,
          ~y=10,
          ~blur=15,
          ~spread=-3,
          ~color=Color.Rgba(0, 0, 0, 0.05),
        )
      ->rounded(~all=5, ())
      ->children([|clickMe, helloWorld|]->React.array)
      ->toReactElement
    );
  };
};

[@react.component]
let make = () => <Container> <Hello /> </Container>;
