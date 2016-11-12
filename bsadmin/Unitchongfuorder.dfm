object frmchongfuorder: Tfrmchongfuorder
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #35746#21333#37325#22797#35746#36135#35760#24405
  ClientHeight = 334
  ClientWidth = 827
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 17
  object DBGrid1: TDBGrid
    Left = 0
    Top = 0
    Width = 827
    Height = 297
    Align = alTop
    DataSource = ds
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentFont = False
    TabOrder = 0
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -12
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'clientname'
        Title.Caption = #23458#25143
        Width = 150
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'OrderNtCode'
        Title.Caption = #35746#21333#21495
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'HdTime'
        Title.Caption = #26085#26399
        Width = 70
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ISBN'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Name'
        Title.Caption = #20070#21517
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Amount'
        Title.Caption = #25968#37327
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'SendAmount'
        Title.Caption = #24050#21457
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'UnsendAmount'
        Title.Caption = #26410#21457
        Width = 50
        Visible = True
      end>
  end
  object RzButton1: TRzButton
    Left = 582
    Top = 303
    Width = 107
    Caption = #32487#32493#25910#35746#27492#20070'(&C)'
    TabOrder = 1
    OnClick = RzButton1Click
  end
  object quit: TRzButton
    Left = 726
    Top = 303
    Caption = #36864#20986'(&Q)'
    TabOrder = 2
    OnClick = quitClick
  end
  object ds: TDataSource
    Left = 408
    Top = 152
  end
  object query: TADOQuery
    Parameters = <>
    Left = 640
    Top = 136
  end
end
