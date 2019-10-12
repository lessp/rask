open Rask;

let card =
  View.(
    make("div")
    ->backgroundColor(White)
    ->display(Flex)
    ->alignItems(Center)
    ->flexDirection(Column)
    ->justifyContent(Center)
    ->height(Px(320))
    ->width(Px(320))
    ->padding(~x=Px(32), ~y=Px(32))
    ->shadow(~x=0, ~y=14, ~blur=22, ~spread=-3, ~color=Rgba(0, 0, 0, 0.15))
    ->rounded(~all=5, ())
  );

let title = text =>
  Text.(
    make(text)
    ->fontFamily("sans-serif")
    ->fontSize(32)
    ->color(Hex("7cc0c0"))
  );
