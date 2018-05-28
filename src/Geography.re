[@bs.module "react-simple-maps"]
external reGeography: ReasonReact.reactClass = "Geography";

let make = (~geography, ~projection, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=reGeography,
    ~props={
        "geography" : geography,
        "projection" : projection
    },
    children,
  );