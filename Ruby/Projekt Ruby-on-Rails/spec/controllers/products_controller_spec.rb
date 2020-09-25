require 'rails_helper'

RSpec.describe ProductsController, type: :controller do
  describe 'PUT #new' do
    subject { put :new }
    let(:admin) { create :admin_user }

    it do
      sign_in admin
      expect(subject.status).to eq(200)
    end
  end

  describe 'PATCH #edit' do
    let(:product) { create :product }
    let(:admin) { create :admin_user }
    subject { patch :edit, params: { id: product.id } }

    it do
      sign_in admin
      expect(subject.status).to eq(200)
    end
  end

  describe 'GET #index' do
    subject { get :index }

    it do
      expect(subject.status).to eq(200)
    end
  end

  describe 'GET #show' do
    let(:product) { create :product }
    subject { get :show, params: { id: product.id } }

    it do
      expect(subject.status).to eq(200)
    end
  end

  describe 'POST #add_to_cart' do
    let(:product) { create :product }
    subject { post :add_to_cart, params: { id: product.id } }
    before do
      allow(AddToCart).to receive(:run).and_return(outcome)
    end

    context 'when guest can add product to cart' do
      let(:outcome) { instance_double(AddToCart, valid?: true) }
      it do
        subject
        expect(controller.flash[:notice]).to eq('Dodano do koszyka')
      end
    end

    context 'when guest can not add product to cart' do
      let(:outcome) { instance_double(AddToCart, valid?: false, errors: errors) }
      let(:errors) { Struct.new(:full_messages).new('Nie można dodać') }

      it do
        subject
        expect(controller.flash[:notice]).to eq('Nie można dodać')
      end

      it do
        expect(subject).to redirect_to(products_path)
      end
    end
  end
end
