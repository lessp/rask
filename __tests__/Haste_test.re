open Jest;
open Expect;
open ReactTestingLibrary;
open Haste;

module Hello = {
  [@react.component]
  let make = () =>
    Text.(
      create("Hello World!")
      |> fontFamily("Roboto")
      |> fontSize(32)
      |> color(Color.Red)
      |> toReactElement
    );
};

describe("Haste", () => {
  afterEach(cleanup);

  test("renders", () =>
    <Hello /> |> render |> container |> expect |> toMatchSnapshot
  );
});
